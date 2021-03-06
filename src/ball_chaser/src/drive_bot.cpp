#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
//TODO: Include the ball_chaser "DriveToTarget" header file
#include "ball_chaser/DriveToTarget.h"

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities

// callback function
bool handle_drive_request_callback(ball_chaser::DriveToTarget::Request& request, ball_chaser::DriveToTarget::Response& response)
{    
  	// twist message instance
    geometry_msgs::Twist motor_command;
    
    // passing values
    motor_command.linear.x = request.linear_x;
    motor_command.angular.z = request.angular_z;
    
  	//publishing topic
    motor_command_publisher.publish(motor_command);
	
  	// generating feedback message
    response.msg_feedback = "linear x: " + std::to_string(request.linear_x) + " & angular z: " + std::to_string(request.angular_z);
  
  	// printing information
  	ROS_INFO_STREAM(response.msg_feedback);
  
    return true;
}

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function
  	// ros::ServiceServer instance
  	ros::ServiceServer service;
  	//advertising service
    service = n.advertiseService("/ball_chaser/command_robot", handle_drive_request_callback);

    // TODO: Delete the loop, move the code to the inside of the callback function and make the necessary changes to publish the requested velocities instead of constant values

    // TODO: Handle ROS communication events
    ros::spin();

    return 0;
}