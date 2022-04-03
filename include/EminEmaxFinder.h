#ifndef EminEmaxFinder_H_
#define EminEmaxFinder_H_

#include "core.h"

class EminEmaxFinder
{
private:
	/**
	 * @brief Finds minimum eigenvalue.
	 */
	double findEmin(const sMatrix& hessian);
	/**
	 * @brief Finds maximum eigenvalue.
	 */
	double findEmax(const sMatrix& hessian);
public:
	EminEmaxFinder()=default;

	std::vector<double> findEminEmax( const std::vector<std::string>& csrFiles);
};
#endif /* EminEmaxFinder_H_ */
