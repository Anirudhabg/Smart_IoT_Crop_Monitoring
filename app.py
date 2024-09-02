import numpy as np

# Known pH values
pH_values = np.array([4.0, 7.0, 10.0])

# Corresponding Analog Values
analog_values = np.array([467, 818, 1012])

# Convert analog values to voltages
voltages = analog_values * 5.0 / 1023.0

# Perform linear regression to find the slope and intercept
slope, intercept = np.polyfit(voltages, pH_values, 1)

print("Slope:", slope)
print("Intercept:", intercept)
