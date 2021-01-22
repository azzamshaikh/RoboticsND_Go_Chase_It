# RoboticsND_Go_Chase_It
Develop a robot (via URDF) and program it to chase a white ball housed in the world developed in the RoboticsND_Build_My_World repo.

![gazebo](RoboticsND_Go_Chase_It.GIF)

# Instructions
1. Create and initialize a catkin workspace `catkin_ws`
> $ mkdir -p /***preferred directory***/catkin_ws/src  
> $ cd /***preferred directory***/catkin_ws/src  
> $ catkin_init_workspace  

2. Clone this repo in a different directory and move the 'ball_chaser' and 'my_robot' package to `src`
3. Go back to the `catkin_ws` directory and and launch the world
> $ cd /catkin_ws  
> $ catkin_make  
> $ source devel/setup.bash  
> $ roslaunch my_robot world.launch  

4. Once launching, RViz and Gazebo World should both launch. In RViz, under the 'Displays' window on the left, under 'Fixed Frame', select 'odom'.
5. Under the 'Displays' window, click and 'Add' and add the following:
  - Under the 'By display type' tab, select RobotModel and click OK
  - Under the 'By topics' tab, click the arrow next to '/image_raw' and select Camera with the 'raw' option and click OK
        OR
     In a new terminal and view the camera through the rqt_image_view node
     > $ cd /catkin_ws  
     > $ source devel/setup.bash  
     > $ rosrun rqt_image_view rqt_image_view  
  - Under the 'By topics' tab, click the '/scan' and click OK  
6. Open a new terminal and go to the `catkin_ws` directory
> $ cd /catkin_ws  
> $ source devel/setup.bash  
> $ roslaunch ball_chaser ball_chaser.launch  

7. Once the ball_chaser has launched, move the white ball outside the entrace with the 'translation mode' feature and place the ball infront of the camera and watch the robot chase the ball!
