"""
Project     : Ultrasonic_Radar
Author      : Stark InnovationZ
Description : Reads angle,cm from the Arduino sketch and shows a live
              polar radar plot with matplotlib.
License     : MIT
"""

import time
import numpy as np
import serial
import matplotlib
import matplotlib.pyplot as plt

matplotlib.use("TkAgg")

# ─── Serial ────────────────────────────────────────────
PORT = "COM27"        # ← change to your port
BAUD = 9600
ser = serial.Serial(PORT, BAUD, timeout=1)
time.sleep(2)
ser.reset_input_buffer()

# ─── Plot setup ───────────────────────────────────────
R_MAX = 100                                     # cm
fig = plt.figure("Ultrasonic RADAR", figsize=(6, 6), facecolor="black")
ax  = fig.add_subplot(111, polar=True, facecolor="#288526")

ax.set_thetamin(0)
ax.set_thetamax(180)
ax.set_theta_zero_location("W")
ax.set_theta_direction(-1)
ax.set_ylim(0, R_MAX)
ax.set_thetagrids(range(0, 181, 30), color="b")
ax.tick_params(axis="both", colors="w")
ax.grid(color="#5adb6d", alpha=.4)

angles    = np.arange(181)
theta_rad = np.deg2rad(angles)
distances = np.zeros_like(angles)

points, = ax.plot([], "", ls="", marker=".", ms=6,
                  mfc="#f1fff1", mec="w")
line, = ax.plot([], [], color="#7aff7b", lw=2)

plt.tight_layout()
plt.ion()
plt.show()

# ─── Main loop ────────────────────────────────────────
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

    points.set_data(theta_rad, distances)
    line.set_data([np.deg2rad(ang)] * 2, [0, R_MAX])

    fig.canvas.draw_idle()
    plt.pause(0.001)

ser.close()
