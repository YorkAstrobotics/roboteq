#include <ros/ros.h>
#include <roboteq_msgs/Command.h>
#include <sensor_msgs/Joy.h>


class rmcjoyconvert
{
  public:
    rmcjoyconvert();

  private:
    void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

    ros::NodeHandle nh_;

    int linear_, angular_;
    double l_scale_, a_scale_;
    ros::Publisher vel_pub_;
    ros::Subscriber joy_sub_;

};


rmcjoyconvert::rmcjoyconvert():
  linear_(1),
  angular_(2)
{   

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);
						

  vel_pub_ = nh_.advertise<roboteq_msgs::Command>("roboteq_driver/cmd", 1);

  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &rmcjoyconvert::joyCallback, this);

}

void rmcjoyconvert::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  roboteq_msgs::Command command;

//if (linear_!=e^-9){
  command.mode = 0;
  command.setpoint = 1000*joy->axes[linear_];
//}
//if (angular_!=e^-9){
 // command.mode = 1;
 // command.setpoint = 1000*joy->axes[angular_];}
  vel_pub_.publish(command);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_turtle");
  rmcjoyconvert teleop_turtle;

  ros::spin();
}






