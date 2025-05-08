import time
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import serial

matplotlib.use("TkAgg")

# ─── serial ────────────────────────────────────────────────────────
PORT = "COM27"
BAUD = 9600
ser = serial.Serial(PORT, BAUD, timeout=1)
time.sleep(2)
ser.reset_input_buffer()

# ─── plot ──────────────────────────────────────────────────────────
R_MAX = 100
fig = plt.figure("Ultra Sonic RADAR", figsize=(6, 6), facecolor="black")
ax  = fig.add_subplot(111, polar=True, facecolor="#288526")

# ── keep only 0-to-180 degrees ─────────────────────────────
ax.set_thetamin(0)        # left edge of the plot
ax.set_thetamax(180)      # right edge of the plot

ax.set_theta_zero_location("W")   # 0° at top
ax.set_theta_direction(-1)        # clockwise
ax.set_ylim(0, R_MAX)
ax.set_thetagrids(range(0, 181, 30), color="b")
ax.tick_params(axis="both", colors="w")
ax.grid(color="#5adb6d", alpha=.4)

angles    = np.arange(181)                  # 0 … 180
theta_rad = np.deg2rad(angles)
distances = np.zeros_like(angles)

points, = ax.plot([], "", ls="", marker=".", ms=6,
                  mfc="#f1fff1", mec="w")
line,   = ax.plot([], [], color="#7aff7b", lw=2)

plt.tight_layout()
plt.ion()                                   # interactive
plt.show()

# ─── main loop ─────────────────────────────────────────────────────
while plt.fignum_exists(fig.number):
    raw = ser.readline().decode("utf-8", "ignore").strip()
    if not raw:
        continue

    try:
        ang, dist = (float(x) for x in raw.split(","))
    except ValueError:
        continue

    if dist > R_MAX:
        dist = 0

    distances[int(ang)] = dist

    # update scatter
    points.set_data(theta_rad, distances)

    # update sweep bar (simple 2-point line)
    line.set_data([np.deg2rad(ang)]*2, [0, R_MAX])

    fig.canvas.draw_idle()
    plt.pause(0.001)            # lets GUI process events

ser.close()
