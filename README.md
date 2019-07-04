# Basic ROS Project
Project for basic understanding of ROS.

### Overview of the project
This project is dedicated with udacity project related with ROS.

ROS is the software platform which provides several functions for Robotics application.

I designed mobile robot which can chases white ball.

The structure of this repository is shows as below.

```
    <repository>                          # Go Chase It Project
    ├── my_robot                       # my_robot package                   
    │   ├── launch                     # launch folder for launch files   
    │   │   ├── robot_description.launch
    │   │   ├── world.launch
    │   ├── meshes                     # meshes folder for sensors
    │   │   ├── hokuyo.dae
    │   ├── urdf                       # urdf folder for xarco files
    │   │   ├── my_robot.gazebo
    │   │   ├── my_robot.xacro
    │   ├── world                      # world folder for world files
    │   │   ├── <yourworld>.world
    │   ├── CMakeLists.txt             # compiler instructions
    │   ├── package.xml                # package info
    ├── ball_chaser                    # ball_chaser package                   
    │   ├── launch                     # launch folder for launch files   
    │   │   ├── ball_chaser.launch
    │   ├── src                        # source folder for C++ scripts
    │   │   ├── drive_bot.cpp
    │   │   ├── process_images.cpp
    │   ├── srv                        # service folder for ROS services
    │   │   ├── DriveToTarget.srv
    │   ├── CMakeLists.txt             # compiler instructions
    │   ├── package.xml                # package info                  
    └──                              
```


### Setting up before cloning this repository
You have to initialize catkin directory before cloning this repository.
Command execution is shown as the following.

```
$ mkdir -p <user_dir>/workspace/catkin_ws/src
$ cd <user_dir>/workspace/catkin_ws/src
$ catkin_init_workspace
```

### Cloning the repository
After initializing catkin directory, you have to clone my repository.

```
$ cd <user_dir>/workspace
$ git clone https://github.com/takam5f2/URN_Project_ROS_Basic
```

You can find URN_Project_ROS_Basic directory in your file system.

You have to move all contents file into `<user_dir>/workspace/catkin_ws/src` directory as below.

```
$ mv <user_dir>/workspace/URN_Project_ROS_Basic/* <user_dir>/workspace/catkin_ws/src/
$ rmdir <user_dir>/workspace/URN_Project_ROS_Basic
```
You can compile the code.


### Compile and execution

You can compile and execute with the following command lines.

##### Compile
```
$ cd <user_dir>/workspace/catkin_ws/
$ catkin_make
```

##### Execution
Please execute the following command line on a terminal.
```
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch my_robot world.launch
```

You have to make another terminal and execute the following.
```
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch ball_chaser ball_chaser.launch
```

You can visualize the image which camera can obtained.
```
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ rosrun rqt_image_view rqt_image_view
```

After executing the commands, you can find that the mobile robot is approaching to the white ball.

