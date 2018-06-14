#include <motion_viewer/RvizPolygonsTools.hpp>

//namespace rviz_visual_tools{

RvizPolygonsTools::RvizPolygonsTools(std::string base_frame, 
                  std::string marker_topic, 
                  ros::NodeHandle nh):RvizVisualTools(base_frame, marker_topic, nh){

}

RvizPolygonsTools::~RvizPolygonsTools(){


}


bool RvizPolygonsTools::publishEigenPath(Eigen::VectorXd & eigen_path_x,
                    Eigen::VectorXd & eigen_path_y,
                    Eigen::VectorXd & eigen_path_z,
                    rviz_visual_tools::colors color,
                    rviz_visual_tools::scales scale,
                    const std::string & ns){

  geometry_msgs::Point temp;
  std::vector<geometry_msgs::Point> trajectory;
  int points_num = eigen_path_x.rows();

  for (std::size_t i = 0; i < points_num; ++i)
    {
      temp.x = eigen_path_x(i);
      temp.y = eigen_path_y(i);
      temp.z = eigen_path_z(i);

      trajectory.push_back(temp);
    }

  publishPath(trajectory, color, scale, ns);
}

bool RvizPolygonsTools::publishTriangle(const Eigen::Affine3d& pose, rviz_visual_tools::colors color, double scale)
{
   return publishTriangle(convertPose(pose), color, scale);
}

bool RvizPolygonsTools::publishTriangle(const geometry_msgs::Pose& pose, rviz_visual_tools::colors color, double scale){
  triangle_marker_.header.stamp = ros::Time::now();
  triangle_marker_.id++;

  triangle_marker_.color = getColor(color);
  triangle_marker_.pose = pose;

  geometry_msgs::Point p[3];
  p[0].x = 1.0 * scale;
  p[0].y = 0.0 * scale;
  p[0].z = 0.0;

  p[1].x = 0.0 * scale;
  p[1].y = -1.0 * scale;
  p[1].z = 0.0;

  p[2].x = 0.0 * scale;
  p[2].y = 1.0 * scale;
  p[2].z = 0.0;

  triangle_marker_.scale.x = 1.0;
  triangle_marker_.scale.y = 1.0;
  triangle_marker_.scale.z = 1.0;

  triangle_marker_.points.clear();
  triangle_marker_.points.push_back(p[0]);
  triangle_marker_.points.push_back(p[1]);
  triangle_marker_.points.push_back(p[2]);


  return publishMarker(triangle_marker_);
}


bool RvizPolygonsTools::publishTriangle(const Eigen::Affine3d& pose, 
                                        Eigen::Vector3d v1,
                                        Eigen::Vector3d v2,
                                        Eigen::Vector3d v3,
                                        bool frame_flag,
                                        rviz_visual_tools::colors color,  
                                        double scale)
{
   return publishTriangle(convertPose(pose), v1, v2, v3, frame_flag, color, scale);
}

bool RvizPolygonsTools::publishTriangle(const geometry_msgs::Pose& pose, 
                                        Eigen::Vector3d v1,
                                        Eigen::Vector3d v2,
                                        Eigen::Vector3d v3,
                                        bool frame_flag,
                                        rviz_visual_tools::colors color,  
                                        double scale){
  if(frame_flag){
    publishTriangleFrame(pose, v1, v2, v3);
  }

  triangle_marker_.header.stamp = ros::Time::now();
  triangle_marker_.id++;

  triangle_marker_.color = getColor(color);
  triangle_marker_.pose = pose;

  geometry_msgs::Point p[3];
  p[0].x = v1(0) * scale;
  p[0].y = v1(1) * scale;
  p[0].z = v1(2);

  p[1].x = v2(0) * scale;
  p[1].y = v2(1) * scale;
  p[1].z = v2(2);

  p[2].x = v3(0) * scale;
  p[2].y = v3(1) * scale;
  p[2].z = v3(2);

  triangle_marker_.scale.x = 1.0;
  triangle_marker_.scale.y = 1.0;
  triangle_marker_.scale.z = 1.0;

  triangle_marker_.points.clear();
  triangle_marker_.points.push_back(p[0]);
  triangle_marker_.points.push_back(p[1]);
  triangle_marker_.points.push_back(p[2]);


  return publishMarker(triangle_marker_);
}

bool RvizPolygonsTools::publishTriangleFrame(const geometry_msgs::Pose& pose, 
                                        Eigen::Vector3d v1,
                                        Eigen::Vector3d v2,
                                        Eigen::Vector3d v3,
                                        rviz_visual_tools::colors color,  
                                        double scale,
                                        const std::string & ns){
  std::vector<geometry_msgs::Point> points;

  geometry_msgs::Point p[4];
  p[0].x = v1(0) + pose.position.x;
  p[0].y = v1(1) + pose.position.y;
  p[0].z = v1(2) + pose.position.z;
  points.push_back(p[0]);

  p[1].x = v2(0) + pose.position.x;
  p[1].y = v2(1) + pose.position.y;
  p[1].z = v2(2) + pose.position.z;
  points.push_back(p[1]);

  p[2].x = v3(0) + pose.position.x;
  p[2].y = v3(1) + pose.position.y;
  p[2].z = v3(2) + pose.position.z;
  points.push_back(p[2]);

  p[3].x = v1(0) + pose.position.x;
  p[3].y = v1(1) + pose.position.y;
  p[3].z = v1(2) + pose.position.z;
  points.push_back(p[3]);

  return publishPath(points, color, scale, ns);
}

bool RvizPolygonsTools::publishQuadrilateral(const Eigen::Affine3d& pose, 
                                        Eigen::Vector3d v1,
                                        Eigen::Vector3d v2,
                                        Eigen::Vector3d v3,
                                        Eigen::Vector3d v4,
                                        bool frame_flag,
                                        rviz_visual_tools::colors color,  
                                        double scale)
{
   return publishQuadrilateral(convertPose(pose), v1, v2, v3, v4, frame_flag, color, scale);
}

bool RvizPolygonsTools::publishQuadrilateral(const geometry_msgs::Pose& pose, 
                                        Eigen::Vector3d v1,
                                        Eigen::Vector3d v2,
                                        Eigen::Vector3d v3,
                                        Eigen::Vector3d v4,
                                        bool frame_flag,
                                        rviz_visual_tools::colors color,  
                                        double scale){

  if(frame_flag){
    publishQuadrilateralFrame(pose, v1, v2, v3, v4);
  }

  triangle_marker_.header.stamp = ros::Time::now();
  triangle_marker_.id++;

  triangle_marker_.color = getColor(color);
  triangle_marker_.pose = pose;

  geometry_msgs::Point p[4];

  p[0].x = v1(0) * scale;
  p[0].y = v1(1) * scale;
  p[0].z = v1(2);

  p[1].x = v2(0) * scale;
  p[1].y = v2(1) * scale;
  p[1].z = v2(2);

  p[2].x = v3(0) * scale;
  p[2].y = v3(1) * scale;
  p[2].z = v3(2);

  p[3].x = v4(0) * scale;
  p[3].y = v4(1) * scale;
  p[3].z = v4(2);

  triangle_marker_.scale.x = 1.0;
  triangle_marker_.scale.y = 1.0;
  triangle_marker_.scale.z = 1.0;

  triangle_marker_.points.clear();
  triangle_marker_.points.push_back(p[0]);
  triangle_marker_.points.push_back(p[1]);
  triangle_marker_.points.push_back(p[2]);

  triangle_marker_.points.push_back(p[2]);
  triangle_marker_.points.push_back(p[3]);
  triangle_marker_.points.push_back(p[0]);

  return publishMarker(triangle_marker_);
}

bool RvizPolygonsTools::publishQuadrilateralFrame(const geometry_msgs::Pose& pose, 
                                        Eigen::Vector3d v1,
                                        Eigen::Vector3d v2,
                                        Eigen::Vector3d v3,
                                        Eigen::Vector3d v4,
                                        rviz_visual_tools::colors color,  
                                        double scale,
                                        const std::string & ns){
  std::vector<geometry_msgs::Point> points;

  geometry_msgs::Point p[5];
  p[0].x = v1(0) + pose.position.x;
  p[0].y = v1(1) + pose.position.y;
  p[0].z = v1(2) + pose.position.z;
  points.push_back(p[0]);

  p[1].x = v2(0) + pose.position.x;
  p[1].y = v2(1) + pose.position.y;
  p[1].z = v2(2) + pose.position.z;
  points.push_back(p[1]);

  p[2].x = v3(0) + pose.position.x;
  p[2].y = v3(1) + pose.position.y;
  p[2].z = v3(2) + pose.position.z;
  points.push_back(p[2]);

  p[3].x = v4(0) + pose.position.x;
  p[3].y = v4(1) + pose.position.y;
  p[3].z = v4(2) + pose.position.z;
  points.push_back(p[3]);

  p[4].x = v1(0) + pose.position.x;
  p[4].y = v1(1) + pose.position.y;
  p[4].z = v1(2) + pose.position.z;
  points.push_back(p[4]);

  return publishPath(points, color, scale, ns);
}

bool RvizPolygonsTools::publishHexahedron(const Eigen::Affine3d& pose, 
                                        Eigen::Vector3d v1,
                                        Eigen::Vector3d v2,
                                        Eigen::Vector3d v3,
                                        Eigen::Vector3d v4,
                                        Eigen::Vector3d v5,
                                        Eigen::Vector3d v6,
                                        Eigen::Vector3d v7,
                                        Eigen::Vector3d v8,
                                        bool frame_flag,
                                        rviz_visual_tools::colors color,  
                                        double scale)
{
   return publishHexahedron(convertPose(pose), v1, v2, v3, v4, v5, v6, v7, v8, frame_flag, color, scale);
}

bool RvizPolygonsTools::publishHexahedron(const geometry_msgs::Pose& pose, 
                                        Eigen::Vector3d v1,
                                        Eigen::Vector3d v2,
                                        Eigen::Vector3d v3,
                                        Eigen::Vector3d v4,
                                        Eigen::Vector3d v5,
                                        Eigen::Vector3d v6,
                                        Eigen::Vector3d v7,
                                        Eigen::Vector3d v8,
                                        bool frame_flag,
                                        rviz_visual_tools::colors color,  
                                        double scale){

  //// plane 1
  publishQuadrilateral(pose, v1, v2, v3, v4, frame_flag, color, scale);

  //// plane 2
  publishQuadrilateral(pose, v5, v6, v7, v8, frame_flag, color, scale);

  //  // plane 3
  publishQuadrilateral(pose, v1, v2, v6, v5, frame_flag, color, scale);

  //    // plane 4
  publishQuadrilateral(pose, v2, v3, v7, v6, frame_flag, color, scale);

  //    // plane 5
  publishQuadrilateral(pose, v3, v4, v8, v7, frame_flag, color, scale);

  //    // plane 6
  publishQuadrilateral(pose, v1, v4, v8, v5, frame_flag, color, scale);

  return publishMarker(triangle_marker_);
}


//}  // namespace rviz_visual_tools