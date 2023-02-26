# Decision Makeing, Planning, and Control in Robotics

Decision making, planning, and control together can make a robot work autonomously. The autonomy work flow for the robot from bottom to top are:

1. **Modelling**: Build the dynamic model of the robot. It include the kinematics and dynamics model. 
>Recommended Readings: [ETH robot dynamics note](https://ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/documents/RobotDynamics2017/RD_HS2017script.pdf)

2. **Control**: Current fashion is use an optimization way to control robotic systems. 
>Recommended Lectures: 
 >- [Youtube lectuers | Stanford Convex Optimization, Boyd](https://www.youtube.com/watch?v=McLq1hEq3UY&list=PL3940DD956CDF0622) 
 >- [Youtube lectures | CMU Optimal Control, Zac Manchester](https://www.youtube.com/watch?v=I2SC1Mp3Hxs&list=PLZnJoM76RM6Iaf59ICcU9-DzztGZvK_52)

3. **Path Plan**: Find a collision free path in 2D or 3D envirnoments. Both search based method like A* or sampling based method like RPM are frequently used solutions.
>Recommended Tools:
>-  [OMPL](https://ompl.kavrakilab.org/)

4. **Trajectory Optimization**: Use the optimization fashion to find out a kinodynamic trajectory. 
>Recommended Lectures:
>- [深蓝学院 Lectures| Motion plannig for mobile robot, Fei Gao](https://www.shenlanxueyuan.com/course/575)
>- [Youtube Lectures| MIT Underactuated Robotics, Russ Tedrake](https://www.youtube.com/watch?v=3g-w88nNW6E&list=PLkx8KyIQkMfXyKku6DstXjD9xU93ptDyc)
>- [Youtube Lectuers| MIT Robotic Manipulation, Russ Tedrake](https://www.youtube.com/watch?v=QlrRb7X4JvA&list=PLkx8KyIQkMfUSDs2hvTWzaq-cxGl8Ha69)

5. **Decision Making**: Use Finite State Machine (FSM) or Behavior Tree (BT) to help the robot decision when and what to act. For complexed envirnoment, BT is better than FSM.
> Recommended Reading: 
> - [Book | Behavior Trees in Robotics and AI: An Introduction](https://arxiv.org/abs/1709.00084)
> - [Framework | BehaviorTree.CPP](https://www.bing.com/search?q=behavior+tree+cpp&form=ANNTH1&refig=8b2b8f82ebcd4637a5e384f0710c6376)
> - [ROS Example | Turtlebot3 behavior demos](https://github.com/sea-bass/turtlebot3_behavior_demos)

For further study, please read paper to learn from the state of the art.