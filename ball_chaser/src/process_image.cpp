#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
  // TODO: Request a service and pass the velocities to it to drive the robot
  ROS_INFO_STREAM("Drive Robot with following lin_x and ang_z");
  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;

  if (!client.call(srv)) {
    ROS_ERROR("Failed to call service /ball_chaser/command_robot");
  }
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    int white_counter_left = 0;
    int white_counter_right = 0;
    int white_counter_center = 0;
    
    for (int i = 0; i < img.height; i++) {
      for (int j = 0; j < img.width; j++) {
        if (img.data[i*img.step+3*j] == white_pixel
            && img.data[i*img.step+3*j+1] == white_pixel
            && img.data[i*img.step+3*j+2] == white_pixel ) {
          if (j < img.width/3)
            white_counter_left++;
          else if (j < img.width/3*2)
            white_counter_center++;
          else
            white_counter_right++;
        }
      }
    }
    ROS_INFO("left: %d, center: %d, right: %d", white_counter_left, white_counter_center, white_counter_right);

    // select the direction or moving forward.
    if (white_counter_left == 0
        && white_counter_center == 0
        && white_counter_right == 0)
      drive_robot(0, 0);
    else if (white_counter_left >= white_counter_center
             && white_counter_left >= white_counter_right)
      drive_robot(0.0, 0.5);
    else if (white_counter_center >= white_counter_left
             && white_counter_center >= white_counter_right)
      drive_robot(0.5, 0.0);
    else if (white_counter_right >= white_counter_left
             && white_counter_right >= white_counter_center)
      drive_robot(0.0, -0.5);
    
    return;
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
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
