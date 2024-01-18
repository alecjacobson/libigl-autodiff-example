#include <igl/doublearea.h>
#include <igl/opengl/glfw/Viewer.h>

#include <autodiff/reverse/var.hpp>
#include <autodiff/reverse/var/eigen.hpp>

int main(int argc, char *argv[])
{
  // read ../decimated-knight.off or argv[1]
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  igl::read_triangle_mesh(
      argc>1?argv[1]:"../decimated-knight.off", V, F);

  // Create autodiff variables of mesh vertex positions
  autodiff::MatrixXvar U = V.cast<autodiff::var>();

  // Compute f = total surface area using our autodiff types
  autodiff::VectorXvar A;
  igl::doublearea(U, F, A);
  autodiff::var f = A.sum()/2.0;

  // Compute the gradient of f with respect to U into a matrix same size as U
  Eigen::MatrixXd dfdU;
  {
    // Autodiff requires variables to be put into a vector
    autodiff::VectorXvar U_vec = autodiff::VectorXvar{U.reshaped()};
    Eigen::VectorXd dfdU_vec = gradient(f, U_vec);
    dfdU = dfdU_vec.reshaped(U.rows(), U.cols());
  }

  // Draw the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.data().set_face_based(true);

  // Draw dfdU as little white lines from each vertex
  const double scale = 
    0.1 * 
    (V.colwise().maxCoeff()-V.colwise().minCoeff()).norm()/
    dfdU.rowwise().norm().maxCoeff();
  viewer.data().add_edges(V,(V + dfdU*scale).eval(), Eigen::RowVector3d(1,1,1) );
  viewer.data().line_width = 1;
  viewer.launch();
}

