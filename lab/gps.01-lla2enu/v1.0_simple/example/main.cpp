
#include <wgs_conversions/wgs_conversions.h>
#include <iostream>
#include <array>
#include <list>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int test_xyz2lla()
{
  WgsConversions conv;

  double xyz[3], lla[3];

  xyz[0] = 422143.588316416;
  xyz[1] = -5361864.950247487;
  xyz[2] = 3417050.753609172;

  std::cout << "\nConverting position\n\tX: " << xyz[0] << "\tY: " << xyz[1] << "\tZ: " << xyz[2] << std::endl;

  // xyz to lla
  conv.xyz2lla(lla, xyz); // Lat: 32.6031    Long: -85.4983  Alt: 164.241

  std::cout << "\n\tSuccessfully converted from ecef to lla" << std::endl;
  std::cout << "\t\tLat: " << lla[0] << "\tLong: " << lla[1] << "\tAlt: " << lla[2] << std::endl;

  return 0;
}

int test_lla2enu()
{
  WgsConversions conv;

  double lla[3], ref_lla[3], enu[3];

  // reference Lat,Long,Alt)
  ref_lla[0] = 25.061676;  // Latitude
  ref_lla[1] = 121.651995; // Longitude
  ref_lla[2] = 0;          // altitude

  // 25.061700,121.652073
  lla[0] = 25.061700;  // Latitude
  lla[1] = 121.652073; // Longitude
  lla[2] = 0;

  // lla to enu
  conv.lla2enu(enu, lla, ref_lla); // Lat: 32.6031    Long: -85.4983  Alt: 164.241

  std::cout << "\n\tSuccessfully converted from lla to enu" << std::endl;
  std::cout << "\t\tLat: " << lla[0] << "\tLong: " << lla[1] << "\tAlt: " << lla[2] << std::endl;
  std::cout << "\t\tref_Lat: " << ref_lla[0] << "\tref_Long: " << ref_lla[1] << "\tref_Alt: " << ref_lla[2] << std::endl;
  std::cout << "\t\tE: " << enu[0] << "\tN: " << enu[1] << "\tU: " << enu[2] << std::endl;

  return 0;
}

// std::copy(arr.begin(), arr.end(), data);
int test_lla2enu_v2()
{
  double lla[3], ref_lla[3], enu[3];
  WgsConversions conv;

  // reference Lat,Long,Alt)
  ref_lla[0] = 35.061676;  // Latitude
  ref_lla[1] = 131.651995; // Longitude
  ref_lla[2] = 0;          // altitude

  std::list<std::array<double, 3>> gpsList;

  gpsList.push_back({35.061739, 131.652172, 0}); // 前進 (64), lat, long
  gpsList.push_back({35.061877, 131.652303, 0}); // 第一個左轉位置 (67)
  gpsList.push_back({35.062719, 131.651996, 0}); // 前進 (77)
  gpsList.push_back({35.063797, 131.651670, 0}); // 開始左轉 (88)
  gpsList.push_back({35.064134, 131.651519, 0}); // 第二個左轉位置 (97)
  gpsList.push_back({35.064021, 131.650956, 0}); // 繼續前進 (157)
  gpsList.push_back({35.062526, 131.645814, 0}); // POI 終點位置 (201)




  std::list<std::array<double, 3>> enuList;

  // Displaying the elements in the list
  for (const auto &arr : gpsList)
  {
    std::cout << "\t\tLat: " << arr[0] << "\tLong: " << arr[1] << "\tAlt: " << arr[2] << std::endl;
    std::copy(arr.begin(), arr.end(), lla); // update the lla point

    conv.lla2enu(enu, lla, ref_lla); // Lat: 32.6031    Long: -85.4983  Alt: 164.241

    std::cout << "\n\tSuccessfully converted from lla to enu" << std::endl;
    std::cout << "\t\tLat: " << lla[0] << "\tLong: " << lla[1] << "\tAlt: " << lla[2] << std::endl;
    std::cout << "\t\tref_Lat: " << ref_lla[0] << "\tref_Long: " << ref_lla[1] << "\tref_Alt: " << ref_lla[2] << std::endl;
    std::cout << "\t\tE: " << enu[0] << "\tN: " << enu[1] << "\tU: " << enu[2] << std::endl;

    enuList.push_back({enu[0], enu[1], enu[2]});
    std::cout << std::endl;
  }

  // print enu list
  for (const auto &enu : enuList)
  {
    std::cout << "\t\tE: " << enu[0] << "\tN: " << enu[1] << "\tU: " << enu[2] << std::endl;
  }

  return 0;
}

int main()
{

  test_xyz2lla();
  test_lla2enu();
  test_lla2enu_v2();

  return 0;
}