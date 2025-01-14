import pymap3d as pm


# Define the origin in LLA
lat0, lon0, alt0 = 25.061676, 121.651995, 0.0  # reference lla 
lat, lon, alt = 25.061700, 121.652073, 0 

# Convert to ENU
e, n, u = pm.geodetic2enu(lat, lon, alt, lat0, lon0, alt0)
print(f"East (E): {e:.2f} meters")
print(f"North (N): {n:.2f} meters")
print(f"Up (U): {u:.2f} meters")

# result
# East (E): 7.87 meters
# North (N): 2.66 meters
# Up (U): -0.00 meters

