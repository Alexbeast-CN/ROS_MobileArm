# ROS_MobileArm

This is a DriveDream internship project. The robot is a 4-wheel differential driven base with a robotic manipulator. The aim of the project is to:

- Build the mobile manipulator's kinematics and dynamic model.
- Simulate and remote control the robot in Gazebo.
- Let the robot navigate autonomously in a known environment.

## Agenda

**Tim:**
* [x] Create the framework of the repo. 
* [x] Add template files.
* [x] Unify the data type.

**Keyu Ge:**

* [x] Learn from [champ](https://github.com/chvmp/champ), which is a good example of how a ROS project should be.
* [ ] Create a package named `kinematics` and do the following tasks:
    * [ ] Build the kinematics model of a 4-wheel differential driven vehicel.

**Yijie Gong:**

* [x] Study ROS2.
* [x] Create a package named `robot_description`  and do the following tasks:
    * [x] Write/build a 4-wheel_robot_model.urdf (or in .xacro, chose one).
    * [x] Display the robot in rviz and gazebo.
* [ ] Read the documents and run some examples [nav2](https://www.bing.com/search?q=nav2&qs=n&form=QBRE&sp=-1&lq=0&pq=nav2&sc=10-4&sk=&cvid=9BBF6F736A604C11ABCCC35839C5A6D4&ghsh=0&ghacc=0&ghpl=) and [moveit2](https://moveit.ros.org/install-moveit2/source/)
* [ ] Replace the simple model with [husky](https://github.com/husky/husky) + [ur5](https://github.com/ros-industrial/universal_robot).

## Log

Please markdown every problem you meet during the intership in the [log](./log/) folder. 

## Learning Resources

If you find any good learning resources please put them into the [learning](./learning/) folder.

