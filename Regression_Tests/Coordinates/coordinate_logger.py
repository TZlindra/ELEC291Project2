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
    columns = ['Datetime', 'Robot X', 'Robot Y', 'Robot Z', 'Controller X', 'Controller Y', 'Controller Z']
)

s = 0
while (robot_port.isOpen()) and (controller_port.isOpen()) and (s < 100):
    print(f'[{dt.datetime.now()}] Reading data...')

    robot_data = robot_port.readline().decode('utf-8').strip('\r\n')
    controller_data = controller_port.readline().decode('utf-8').strip('\r\n')

    robot_coordinates = robot_data.split(',')
    try :
        robot_x = float(robot_coordinates[0].split(':')[1])
        robot_y = float(robot_coordinates[1].split(':')[1])
        robot_z = float(robot_coordinates[2].split(':')[1])
    except:
        robot_x, robot_y, robot_z = np.nan, np.nan, np.nan

    controller_coordinates = controller_data.split(',')
    try :
        controller_x = float(controller_coordinates[0].split(':')[1])
        controller_y = float(controller_coordinates[1].split(':')[1])
        controller_z = float(controller_coordinates[2].split(':')[1])
    except:
        controller_x, controller_y, controller_z = np.nan, np.nan, np.nan

    new_df = pd.DataFrame(
        {
            'Datetime': [dt.datetime.now()],
            'Robot X': [robot_x],
            'Robot Y': [robot_y],
            'Robot Z': [robot_z],
            'Controller X': [controller_x],
            'Controller Y': [controller_y],
            'Controller Z': [controller_z]
    })

    if log_df.empty:
        log_df = new_df
    else:
        log_df = pd.concat([log_df, new_df], ignore_index=True)

    s += 1

display(log_df)
log_df.to_csv('Coordinate_Logs.csv', index=False)

fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(15, 10))  # Create two subplots

# Subplot for Controller X vs Robot X
ax1.set_title('X Coordinates', size=18)  # Set title
ax1.set_ylim(-105, 105)  # Set y-axis limits
ax1.scatter(
    log_df.index,
    log_df['Controller X'],
    label='Controller TX',
    color='blue',
    alpha=0.5  # Set transparency
)
ax1.scatter(
    log_df.index,
    log_df['Robot X'],
    label='Robot RX',
    color='red',
    alpha=0.5  # Set transparency
)
ax1.grid(True, color='black')
ax1.tick_params(axis='x', colors='black')
ax1.tick_params(axis='y', colors='black')
ax1.set_axisbelow(True)
ax1.set_facecolor('white')
ax1.set_ylabel('Value', size=15)  # Set y-axis label
ax1.legend(loc='upper left', bbox_to_anchor=(1, 1), borderaxespad=1.)  # Place legend to the right

# Subplot for Controller Y vs Robot Y
ax2.set_title('Y Coordinates', size=18)  # Set title
ax2.set_ylim(-105, 105)  # Set y-axis limits
ax2.scatter(
    log_df.index,
    log_df['Controller Y'],
    label='Controller TX',
    color='blue',
    alpha=0.5  # Set transparency
)
ax2.scatter(
    log_df.index,
    log_df['Robot Y'],
    label='Robot RX',
    color='red',
    alpha=0.5  # Set transparency
)
ax2.grid(True, color='black')
ax2.set_facecolor('white')
ax2.set_xlabel('Samples', size=15)  # Set x-axis label
ax2.set_ylabel('Value', size=15)  # Set y-axis label
ax2.legend(loc='upper left', bbox_to_anchor=(1, 1), borderaxespad=1.)  # Place legend to the right
ax2.tick_params(axis='x', colors='black')  # Rotate x-axis labels for readability

fig.suptitle('JDY40 : Movement Controls', fontsize=25, color='black')

fig.tight_layout()  # Adjust layout to prevent overlap
plt.show()

# Note: To save the figure, plt.savefig should be used before plt.show()
fig.savefig('Coordinate_Logs.jpg')
