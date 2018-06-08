#include "PID.h"
#include <iostream>
#include <cmath>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
	 Kp=Kp_;
	 Ki=Ki_;
	Kd=Kd_;
	p_error = 0;
	i_error = 0;
	d_error = 0;


}

void PID::UpdateError(double cte) {
	// d_error is difference from old cte (p_error) to the new cte
	d_error = (cte - p_error);
	// p_error gets set to the new cte
	p_error = cte;
	// i_error is the sum of ctes to this point
	i_error += cte;
	counter += 1;
}

double PID::TotalError() {
	
	return -Kp * p_error - Kd * d_error - Ki * i_error;
}


void PID::Twiddle(double tol = 0.2 ) {

	double dp[3] = { 0.5,0.5,0.5 };
	 p[0] = Kp;
	 p[1]=Ki;
	p[2]=Kd;
	
	double best_error = -Kp * p_error -Kd * d_error -Ki * i_error;
	while ((std::abs(dp[0])+std::abs(dp[1])+std::abs(dp[2])) > tol)
	
	{
		
		for (int i = 2; i < 3; i++) {
			p[i] += dp[i];
			Kp = p[0];
			Ki = p[1];
			Kd = p[2];
			double error = TotalError();
			if (std::abs(error) < std::abs(best_error))
			{
				
				best_error = error;
				dp[i] *= 1.1;
			}
			else

			{				
				p[i] -= 2 * dp[i];
				Kp = p[0];
				Ki = p[1];
				Kd = p[2];
				error = TotalError();
				if (std::abs(error) < std::abs(best_error))
				{
					
					best_error = error;
					dp[i] *= 1.1;
				}
				else
				{
					
					p[i] += dp[i];
					dp[i] *= 0.9;
				}

			}
		}

	}
	
	Kp = p[0];
	Ki = p[1];
	Kd = p[2];


	cout << "Entered twiddle!" << endl;
	cout << Kp <<" "<<Ki<<" "<<Kd<< endl;
}


