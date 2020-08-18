#include "ceres/ceres.h"
#include "glog/logging.h"

using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solve;
using ceres::Solver;

struct ExponentialResidual
{
	ExponentialResidual(double x, double y) : x_(x), y_(y)
	{
	
	}

	template <typename T> bool operator()(const T* const m, const T* const c, T* residual) const
	{
		residual[0] = pow((T(y_) - m[0] * T(x_) + c[0]),2);
		return true;
	}

	private:
	// Observations for a sample.
	const double x_;
	const double y_;
};

int main(int argc, char** argv)
{
	google::InitGoogleLogging(argv[0]);
	
	int n;
	std::cin>>n;
	
	double data[2*n];
	
	for(int j=0; j<2*n; j++)
	{
		//std::cout<<"a["<<(j-1)/2<<"]";
		std::cin>>data[j];
	}
	int kNumObservations=2*n;
	
	double m = 0.0;
	double c = 0.0;

	Problem problem;

	for (int i = 0; i < kNumObservations; ++i)
	{
		  CostFunction* cost_function = new AutoDiffCostFunction<ExponentialResidual, 1, 1, 1>(new ExponentialResidual(data[2 * i], data[2 * i + 1]));
		  problem.AddResidualBlock(cost_function, NULL, &m, &c);
	}

	Solver::Options options;
	options.max_num_iterations=25;
	options.linear_solver_type=ceres::DENSE_QR;
	options.minimizer_progress_to_stdout=true;
	
	Solver::Summary summary;
	Solve(options,&problem,&summary);
	std::cout << summary.BriefReport() << "\n";
	std::cout << "m : " << m << " c : " << c << "\n";
	return 0;
}

