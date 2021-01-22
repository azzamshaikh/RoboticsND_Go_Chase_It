#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z){
  // Request a service and pass the velocities to it to drive the robot
  ROS_INFO_STREAM("Moving robot at specified velocities");
  
  // Request target position
  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;
  
  // Call the service and pass the requested velocities
  if(!client.call(srv))
    ROS_ERROR("Failed to call service");

}

// This callback function continuously executes andd reads the image data
void process_image_callback(const sensor_msgs::Image img){
  //
  
  int white_pixel = 255;
  int row; 
  // Loop through each pixel in the image and check if there is a white pixel (via checking RGB channels)
  for(int i=0; i < img.height * img.step; i++){
    if((img.data[i] == white_pixel) && (img.data[i+1] == white_pixel) && (img.data[i+2] == white_pixel)){
      row = i % img.step;
      break;
    }
  }
    
  // Identify if this pixel falls in the left, mid, or right side of the image
  // Depending on the white ball position, call the drive_bot function and pass velocities to it
  int left = img.step/3;
  int right = 2*(img.step/3);
  if(row >= 0 && row < left){
    drive_robot(0.0,0.5);
  } 
  else if(row > left && row < right){
    drive_robot(0.5,0.0);
  }
  else if(row > right && row <= img.step){
    drive_robot(0.0,-0.5);
  }
  // Request a stop when there's no white ball seen by the camera
  else{
    drive_robot(0.0,0.0);   
  }

}


int main(int argc, char** argv){
  //Initialize the process_image node andd create a handle to it
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;
  
  // Define a client service capable of requesting services from command_robot
  client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
  
  // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
  ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);
  
  // Handle ROS communication events
  ros::spin();
  
  return 0;
}
