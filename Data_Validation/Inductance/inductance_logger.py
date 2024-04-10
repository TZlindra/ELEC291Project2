import serial
import datetime as dt
import pandas as pd
import numpy as np
from IPython.display import display

import matplotlib.pyplot as plt

ROBOT_COM_PORT = 'COM14'
CONTROLLER_COM_PORT = 'COM4'

robot_port = serial.Serial(
    port = ROBOT_COM_PORT,
    baudrate = 115200,
    parity = serial.PARITY_NONE,
    stopbits = serial.STOPBITS_ONE,
    bytesize = serial.EIGHTBITS
)

controller_port = serial.Serial(
    port = CONTROLLER_COM_PORT,
    baudrate = 115200,
    parity = serial.PARITY_NONE,
    stopbits = serial.STOPBITS_ONE,
    bytesize = serial.EIGHTBITS
)

log_df = pd.DataFrame(
    columns = ['Datetime', 'Robot Inductance', 'Controller Inductance']
)

s = 0
while (robot_port.isOpen()) and (controller_port.isOpen()) and (s < 100):
    print(f'[{dt.datetime.now()}] Reading data...')

    robot_data = robot_port.readline().decode('utf-8').strip('\r\n')
    controller_data = controller_port.readline().decode('utf-8').strip('\r\n')

    try :
        robot_inductance = float(robot_data)
    except:
        robot_inductance = np.nan

    try :
        controller_inductance = float(controller_data)
    except:
        controller_inductance = np.nan

    print(f'[{dt.datetime.now()}] Robot: {robot_data}')
    print(f'[{dt.datetime.now()}] Controller: {controller_data}')

    new_df = pd.DataFrame({
        'Datetime': [dt.datetime.now()],
        'Robot Inductance': [robot_inductance],
        'Controller Inductance': [controller_inductance]
    })

    if log_df.empty:
        log_df = new_df
    else:
        log_df = pd.concat([log_df, new_df], ignore_index=True)

    s += 1

display(log_df)
log_df.to_csv('Inductance_Logs.csv', index=False)

fig, ax1 = plt.subplots(figsize=(15, 5))  # Create one subplot

# Plot for inductance values
ax1.set_ylim(400, 500)  # Set y-axis limits to 400-500 as specified
ax1.scatter(
    log_df.index,
    log_df['Robot Inductance'],
    label='Robot TX',
    color='red',
    alpha=0.5  # Set transparency
)
ax1.scatter(
    log_df.index,
    log_df['Controller Inductance'],
    label='Controller RX',
    color='blue',
    alpha=0.5  # Set transparency
)
ax1.grid(True, color='black')
ax1.tick_params(axis='x', colors='black')
ax1.tick_params(axis='y', colors='black')
ax1.set_axisbelow(True)
ax1.set_facecolor('white')
ax1.set_xlabel('Samples', size=15)  # Set x-axis label
ax1.set_ylabel('Inductance (μH)', size=15)  # Set y-axis label
ax1.legend(loc='upper left', bbox_to_anchor=(1, 1), borderaxespad=1.)  # Place legend to the right

# Set a common title for the figure
fig.suptitle('JDY40 : Inductance Calculation', fontsize=25, color='black')

fig.tight_layout()  # Adjust layout to prevent overlap
plt.show()

# Save the figure
fig.savefig('Inductance_Logs.jpg')
