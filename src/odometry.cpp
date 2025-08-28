#include "odometry.h"
#include <cmath>
#include <ctime>
#include <iterator>
#include <numeric>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

Odometry::Odometry(double wheel_radius, double rpm)
    : radius(wheel_radius), rpm(rpm) {
  // Linear velocity (m/s) =(wheel circumference * revolutions per second)
  double rps = rpm / 60.0;
  linear_vel = 2 * M_PI * radius * rps;
}

double Odometry::distance(int x1, int y1, int x2, int y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double Odometry::angle(int x1, int y1, int x2, int y2) {
  // atan2 returns radians, convert to degrees
  return atan2(y2 - y1, x2 - x1) * 180.0 / M_PI;
}

MotionCommand Odometry::computeCommands(vector<pair<int, int>> &path) {

  MotionCommand res = {0.0, 0.0}; // store total time and angle traversed

  if (path.size() < 2) {
    return res; // No movement needed
  }
  
  double totalDistance = 0.0;
  double totalAngle = 0.0;
  
  // Calculate total distance
  for (size_t i = 0; i < path.size() - 1; i++) {
    double dist = distance(path[i].first, path[i].second, 
                          path[i+1].first, path[i+1].second);
    totalDistance += dist;
  }
  
  // Calculate total angle as sum of all direction angles
  for (size_t i = 0; i < path.size() - 1; i++) {
    double segmentAngle = angle(path[i].first, path[i].second,
                               path[i+1].first, path[i+1].second);
    // Add absolute value of each segment angle
    totalAngle += abs(segmentAngle);
  }
  
  // Time = distance / velocity (each grid cell is 1 meter)
  res.time_sec = totalDistance / linear_vel;
  res.angle_deg = totalAngle;

  return res;
}
