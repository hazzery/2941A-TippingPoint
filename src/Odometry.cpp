#include <cmath>
#include "Odometry.h"

namespace Cory_Odom
{

Odometry::Odometry(const float _distance_between_wheels) : 
distance_between_wheels_(_distance_between_wheels) { }

double Odometry::GetX() {return global_x_; }
double Odometry::GetY() {return global_y_; }

void Odometry::CalculatePosition(const double _left_encoder,const double _right_encoder, const double _tracking_encoder, const float _gyroscope)
{
    static double 
    local_vertical_position, local_horizontal_position,
    change_x, change_y, 
    prev_local_horizontal_position, prev_local_vertical_position;
    static double global_change_x, global_change_y, 
    gyroscope_radians, sin_gyroscope, cos_gyroscope;

    local_vertical_position = (_left_encoder + _right_encoder) / 2; // Calculate the local position relative to the current heading
    local_horizontal_position = _tracking_encoder;

    change_x = local_horizontal_position - prev_local_horizontal_position; // Calculate the change in position between the current 
    change_y = local_vertical_position - prev_local_vertical_position;     // and previous cycle

    prev_local_horizontal_position = local_horizontal_position;
    prev_local_vertical_position = local_vertical_position;

    gyroscope_radians = _gyroscope * degrees_to_radians_; // Reduced repeated calculations
    sin_gyroscope = sin(gyroscope_radians);
    cos_gyroscope = cos(gyroscope_radians);

    global_change_x = change_y * sin_gyroscope - change_x * cos_gyroscope; // Transform the local movement into the global space
	global_change_y = change_x * sin_gyroscope - change_y * cos_gyroscope;

    global_x_ += global_change_x; // Add position change to current position
    global_y_ += global_change_y;
}

template <typename EncoderUnits>
void Odometry::CalculatePosition(const EncoderUnits _left_encoder, const EncoderUnits _right_encoder, const float _gyroscope, const float _dt)
{
    static EncoderUnits change_x, change_y, previous_left_encoder = 0, previous_right_encoder = 0;
    static float linear_velocity, linear_velocity_x, linear_velocity_y;

    change_x = _left_encoder - previous_left_encoder;
    change_y = _right_encoder - previous_right_encoder;

    previous_left_encoder = _left_encoder;
    previous_right_encoder = _right_encoder;

    linear_velocity = (change_x + change_y) / 2;

    linear_velocity_x = linear_velocity * sin(_gyroscope);
    linear_velocity_y = linear_velocity * cos(_gyroscope);

    global_x_ += linear_velocity_x * _dt;
    global_y_ += linear_velocity_y * _dt;
}
}