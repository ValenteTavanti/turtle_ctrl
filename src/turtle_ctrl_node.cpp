#include "rclcpp/rclcpp.hpp"
#include "turtlesim_msgs/msg/pose.hpp"

using std::placeholders::_1;

//topic dal quale leggere la posizione
//tipo messaggio posizione: turtlesim msgs/msg/Pose

class TurtleCtrl:public rclcpp::Node
{
    //subscriber al topic
    rclcpp::Subscription<turtlesim_msgs::msg::Pose>::SharedPtr poseSubscriber_;
    //variable in cui salviamo la posizione letta dal subsrciber
    turtlesim_msgs::msg::Pose poseMsg_;

public:
//costruttore della classe
    TurtleCtrl():Node("turtle_ctrl_node")
    {
        poseSubscriber_=this->create_subscription<turtlesim_msgs::msg::Pose>
        ("/turtle1/pose",10,std::bind(&TurtleCtrl::PoseCallback,this,_1));
    }

    void PoseCallback(const turtlesim_msgs::msg::Pose::SharedPtr msg)
    {
        //stampa la posizione di turtle1
        poseMsg_=*msg;
        std::cout<<"Pose(x,y,θ): "<<poseMsg_.x<<", "<<poseMsg_.y<<", "<<poseMsg_.theta<<std::endl;
    }
};

int main(int argc,char *argv[])
{
    //inizializzo ROS
    rclcpp::init(argc,argv);
    //definisco e lancio il nodo
    std::shared_ptr ctrlNode=std::make_shared<TurtleCtrl>();
    rclcpp::spin(ctrlNode);
    //al termine (Ctrl+C) chiudo ROS
    rclcpp::shutdown();
    return 0;
}