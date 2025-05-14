from vpython import canvas, box, vector, rate, label, cylinder, compound
import serial, numpy as np

# ───── Serial Setup ─────
SERIAL_PORT = "COM6"    # ← Change to your port
BAUD        = 115200
ser = serial.Serial(SERIAL_PORT, BAUD, timeout=1)
print("Serial connected:", SERIAL_PORT)

# ───── Math Helpers ─────
def euler_to_matrix(yaw, pitch, roll):
    y, p, r = np.radians([yaw, pitch, roll])
    cy, sy = np.cos(y), np.sin(y)
    cp, sp = np.cos(p), np.sin(p)
    cr, sr = np.cos(r), np.sin(r)
    return np.array([
        [cy*cp, cy*sp*sr - sy*cr, cy*sp*cr + sy*sr],
        [sy*cp, sy*sp*sr + cy*cr, sy*sp*cr - cy*sr],
        [-sp,   cp*sr,            cp*cr]
    ])

def matrix_to_axis_up(mat):
    axis = vector(mat[0,0], mat[0,1], mat[0,2])
    up   = vector(mat[2,0], mat[2,1], mat[2,2])
    return axis, up

# ───── VPython Scene (inline) ─────
scene = canvas(
    title="MPU-6050 Controlled Car",
    width=500, height=500,
    center=vector(0,0,0),
    background=vector(1,1,1),
    notebook=True          # ← render inline instead of opening a browser window
)
scene.autoscale = False

# ───── Build the Car ─────
body   = box(pos=vector(0,0,0),   size=vector(6,1.2,3), color=vector(0.2,0.6,0.8))
hood   = box(pos=vector(-2.8,0.3,0), size=vector(2,0.6,2.4), color=vector(0.8,0.2,0.2))
dickey = box(pos=vector(2.8,0.3,0),  size=vector(2,0.6,2.4), color=vector(0.2,0.8,0.2))
wheel_r = 0.6
w1 = cylinder(pos=vector(-2.5,-0.6, 1.5), axis=vector(0,0,1), radius=wheel_r, length=0.5)
w2 = cylinder(pos=vector(-2.5,-0.6,-2.0), axis=vector(0,0,1), radius=wheel_r, length=0.5)
w3 = cylinder(pos=vector( 2.5,-0.6, 1.5), axis=vector(0,0,1), radius=wheel_r, length=0.5)
w4 = cylinder(pos=vector( 2.5,-0.6,-2.0), axis=vector(0,0,1), radius=wheel_r, length=0.5)

car = compound([body, hood, dickey, w1, w2, w3, w4])

# ───── Data Label (moved further down) ─────
data_label = label(
    pos=vector(0, -5, 0),      # ← y = -5 for extra space
    text="Yaw: 0°, Pitch: 0°, Roll: 0°",
    height=16,
    box=False,
    color=vector(0,0,0)
)

# ───── Initial Offsets ─────
yaw_offset = pitch_offset = roll_offset = 0.0
while True:
    line = ser.readline().decode().strip()
    if not line: continue
    try:
        y0, p0, r0 = (float(v) for v in line.split(','))
        yaw_offset, pitch_offset, roll_offset = y0, p0, r0
        print(f"Initial offsets set: Yaw={y0}, Pitch={p0}, Roll={r0}")
        break
    except ValueError:
        continue

# ───── Main Loop ─────
while True:
    rate(100)
    line = ser.readline().decode().strip()
    if not line: continue
    try:
        y, p, r = (float(v) for v in line.split(','))
    except ValueError:
        continue

    # zeroed readings
    yaw   = y - yaw_offset
    pitch = p - pitch_offset
    roll  = r - roll_offset

    # update orientation
    R = euler_to_matrix(yaw, pitch, roll)
    axis, up = matrix_to_axis_up(R)
    car.axis = axis
    car.up   = up

    # update label
    data_label.text = f"Yaw: {yaw:.2f}°, Pitch: {pitch:.2f}°, Roll: {roll:.2f}°"
