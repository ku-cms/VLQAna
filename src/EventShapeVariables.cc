#include "Analysis/VLQAna/interface/EventShapeVariables.h"

#include "TMath.h"

/// constructor from XYZ coordinates
  vlq::EventShapeVariables::EventShapeVariables(const std::vector<math::XYZVector>& inputVectors) 
: inputVectors_(inputVectors)
{}

/// constructor from rho eta phi coordinates
vlq::EventShapeVariables::EventShapeVariables(const std::vector<math::RhoEtaPhiVector>& inputVectors)
{
  inputVectors_.reserve( inputVectors.size() );
  for ( std::vector<math::RhoEtaPhiVector>::const_iterator vec = inputVectors.begin(); vec != inputVectors.end(); ++vec ){
    inputVectors_.push_back(math::XYZVector(vec->x(), vec->y(), vec->z()));
  }
}

/// constructor from r theta phi coordinates
vlq::EventShapeVariables::EventShapeVariables(const std::vector<math::RThetaPhiVector>& inputVectors)
{
  inputVectors_.reserve( inputVectors.size() );
  for(std::vector<math::RThetaPhiVector>::const_iterator vec = inputVectors.begin(); vec != inputVectors.end(); ++vec ){
    inputVectors_.push_back(math::XYZVector(vec->x(), vec->y(), vec->z()));
  }
}

/// the return value is 1 for spherical events and 0 for events linear in r-phi. This function 
/// needs the number of steps to determine how fine the granularity of the algorithm in phi 
/// should be
double 
vlq::EventShapeVariables::isotropy(unsigned int numberOfSteps) const
{
  const double deltaPhi=2*TMath::Pi()/numberOfSteps;
  double phi = 0, eIn =-1., eOut=-1.;
  for(unsigned int i=0; i<numberOfSteps; ++i){
    phi+=deltaPhi;
    double sum=0;
    for(unsigned int j=0; j<inputVectors_.size(); ++j){
      // sum over inner product of unit vectors and momenta
      sum+=TMath::Abs(TMath::Cos(phi)*inputVectors_[j].x()+TMath::Sin(phi)*inputVectors_[j].y());
    }
    if( eOut<0. || sum<eOut ) eOut=sum;
    if( eIn <0. || sum>eIn  ) eIn =sum;
  }
  return (eIn-eOut)/eIn;
}

/// the return value is 1 for spherical and 0 linear events in r-phi. This function needs the
/// number of steps to determine how fine the granularity of the algorithm in phi should be
double 
vlq::EventShapeVariables::circularity(unsigned int numberOfSteps) const
{
  const double deltaPhi=2*TMath::Pi()/numberOfSteps;
  double circularity=-1, phi=0, area = 0;
  for(unsigned int i=0;i<inputVectors_.size();i++) {
    area+=TMath::Sqrt(inputVectors_[i].x()*inputVectors_[i].x()+inputVectors_[i].y()*inputVectors_[i].y());
  }
  for(unsigned int i=0; i<numberOfSteps; ++i){
    phi+=deltaPhi;
    double sum=0, tmp=0.;
    for(unsigned int j=0; j<inputVectors_.size(); ++j){
      sum+=TMath::Abs(TMath::Cos(phi)*inputVectors_[j].x()+TMath::Sin(phi)*inputVectors_[j].y());
    }
    tmp=TMath::Pi()/2*sum/area;
    if( circularity<0 || tmp<circularity ){
      circularity=tmp;
    }
  }
  return circularity;
}

/// helper function to fill the 3 dimensional momentum tensor from the inputVecotrs where needed
TMatrixDSym 
vlq::EventShapeVariables::compMomentumTensor(double r) const
{
  TMatrixDSym momentumTensor(3);
  momentumTensor.Zero();

  if ( inputVectors_.size() < 2 ){
    return momentumTensor;
  }

  // fill momentumTensor from inputVectors
  double norm = 0.;
  for ( int i = 0; i < (int)inputVectors_.size(); ++i ){
    double p2 = inputVectors_[i].P()*inputVectors_[i].P();
    if( p2 == 0 ){ p2 = 1; }
    double pR = ( r == 2. ) ? p2 : TMath::Power(p2, 0.5*r);
    norm += pR;
    double pRminus2 = ( r == 2. ) ? 1. : TMath::Power(p2, 0.5*r - 1.);
    momentumTensor(0,0) += pRminus2*inputVectors_[i].x()*inputVectors_[i].x();
    momentumTensor(0,1) += pRminus2*inputVectors_[i].x()*inputVectors_[i].y();
    momentumTensor(0,2) += pRminus2*inputVectors_[i].x()*inputVectors_[i].z();
    momentumTensor(1,0) += pRminus2*inputVectors_[i].y()*inputVectors_[i].x();
    momentumTensor(1,1) += pRminus2*inputVectors_[i].y()*inputVectors_[i].y();
    momentumTensor(1,2) += pRminus2*inputVectors_[i].y()*inputVectors_[i].z();
    momentumTensor(2,0) += pRminus2*inputVectors_[i].z()*inputVectors_[i].x();
    momentumTensor(2,1) += pRminus2*inputVectors_[i].z()*inputVectors_[i].y();
    momentumTensor(2,2) += pRminus2*inputVectors_[i].z()*inputVectors_[i].z();
  }

  //std::cout << "momentumTensor:" << std::endl;
  //std::cout << momentumTensor(0,0) << " " << momentumTensor(0,1) << " " << momentumTensor(0,2) 
  //          << momentumTensor(1,0) << " " << momentumTensor(1,1) << " " << momentumTensor(1,2) 
  //        << momentumTensor(2,0) << " " << momentumTensor(2,1) << " " << momentumTensor(2,2) << std::endl;

  // return momentumTensor normalized to determinant 1
  return (1./norm)*momentumTensor;
}

/// helper function to fill the 3 dimensional vector of eigen-values;
/// the largest (smallest) eigen-value is stored at index position 0 (2)
TVectorD
vlq::EventShapeVariables::compEigenValues(double r) const
{
  TVectorD eigenValues(3);
  TMatrixDSym myTensor = compMomentumTensor(r);
  if( myTensor.IsSymmetric() ){
    if( myTensor.NonZeros() != 0 ) myTensor.EigenVectors(eigenValues);
  }

  // CV: TMatrixDSym::EigenVectors returns eigen-values and eigen-vectors
  //     ordered by descending eigen-values, so no need to do any sorting here...
  //std::cout << "eigenValues(0) = " << eigenValues(0) << ","
  //        << " eigenValues(1) = " << eigenValues(1) << ","
  //        << " eigenValues(2) = " << eigenValues(2) << std::endl;

  return eigenValues;
}

/// 1.5*(q1+q2) where 0<=q1<=q2<=q3 are the eigenvalues of the momentum tensor sum{p_j[a]*p_j[b]}/sum{p_j**2} 
/// normalized to 1. Return values are 1 for spherical, 3/4 for plane and 0 for linear events
double 
vlq::EventShapeVariables::sphericity(double r) const
{
  TVectorD eigenValues = compEigenValues(r);
  double esum = eigenValues.Sum();
  return 1.5*(eigenValues(1) + eigenValues(2))/esum;
}

/// 1.5*q1 where 0<=q1<=q2<=q3 are the eigenvalues of the momentum tensor sum{p_j[a]*p_j[b]}/sum{p_j**2} 
/// normalized to 1. Return values are 0.5 for spherical and 0 for plane and linear events
double 
vlq::EventShapeVariables::aplanarity(double r) const
{
  TVectorD eigenValues = compEigenValues(r);
  double esum = eigenValues.Sum();
  return 1.5*eigenValues(2)/esum;
}

/// 3.*(q1*q2+q1*q3+q2*q3) where 0<=q1<=q2<=q3 are the eigenvalues of the momentum tensor sum{p_j[a]*p_j[b]}/sum{p_j**2} 
/// normalized to 1. Return value is between 0 and 1 
/// and measures the 3-jet structure of the event (C vanishes for a "perfect" 2-jet event)
double 
vlq::EventShapeVariables::C(double r) const
{
  TVectorD eigenValues = compEigenValues(r);
  double esum = eigenValues.Sum();
  return 3.*(eigenValues(0)*eigenValues(1) + eigenValues(0)*eigenValues(2) + eigenValues(1)*eigenValues(2))/(esum*esum);
}

/// 27.*(q1*q2*q3) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor sum{p_j[a]*p_j[b]}/sum{p_j**2} 
/// normalized to 1. Return value is between 0 and 1 
/// and measures the 4-jet structure of the event (D vanishes for a planar event)
double 
vlq::EventShapeVariables::D(double r) const
{
  TVectorD eigenValues = compEigenValues(r);
  double esum = eigenValues.Sum();
  return 27.*eigenValues(0)*eigenValues(1)*eigenValues(2)/(esum*esum*esum);
}


double
vlq::EventShapeVariables::thrust( unsigned int numberOfSteps ) const
{

	TVectorD eigenValues = compEigenValues(1);

/*  const double deltaPhi=2*TMath::Pi()/numberOfSteps;
  const double deltaRho=TMath::Pi()/numberOfSteps;
  double thrust=-1;
  double phi=0;
  double rho=0;
  double area = 0;
  for (int i = 0; i < (int)inputVectors_.size(); ++i ){
    area+=sqrt(inputVectors_[i].X()*inputVectors_[i].X()+inputVectors_[i].Y()*inputVectors_[i].Y()+inputVectors_[i].Z()*inputVectors_[i].Z());
  }
  for(unsigned int i=0; i<numberOfSteps; ++i){
    phi+=deltaPhi; 
    for(unsigned int k=0; k<numberOfSteps; ++k){
      rho+=deltaRho;
      double asum=0;
      double tmp=0;
      for(unsigned int j=0; j<inputVectors_.size(); ++j){
        asum+=abs(cos(phi)*cos(rho)*inputVectors_[j].X()+sin(phi)*cos(rho)*inputVectors_[j].Y()+sin(rho)*inputVectors_[j].Z());
      }
      tmp=asum/area;
      if( thrust<0 || tmp>thrust ){
        thrust=tmp;
      }
    }
  }
*/
  return eigenValues(0);

}


double
vlq::EventShapeVariables::thrustminor( unsigned int numberOfSteps ) const
{

	TVectorD eigenValues = compEigenValues(1);	
 /* const double deltaPhi=2*TMath::Pi()/numberOfSteps;
  const double deltaRho=TMath::Pi()/numberOfSteps;
  double thrust=10;
  double phi=0;
  double rho=0;
  double area = 0;
  for (int i = 0; i < (int)inputVectors_.size(); ++i ){
    area+=sqrt(inputVectors_[i].X()*inputVectors_[i].X()+inputVectors_[i].Y()*inputVectors_[i].Y()+inputVectors_[i].Z()*inputVectors_[i].Z());
  }
  for(unsigned int i=0; i<numberOfSteps; ++i){
    phi+=deltaPhi;
    for(unsigned int k=0; k<numberOfSteps; ++k){
      rho+=deltaRho;
      double asum=0;
      double tmp=2;
      double xs=0;
      double ys=0; 
      double zs=0;
      for(unsigned int j=0; j<inputVectors_.size(); ++j){
        xs = sin(phi)*cos(rho)*inputVectors_[j].Z() - sin(rho)*inputVectors_[j].Y();
        ys = sin(rho)*inputVectors_[j].X() - cos(phi)*cos(rho)*inputVectors_[j].Z();
        zs = cos(phi)*cos(rho)*inputVectors_[j].Y() - sin(phi)*cos(rho)*inputVectors_[j].X();
        asum+=sqrt(xs*xs+ys*ys+zs*zs);
      }
      tmp=asum/area;
      if( thrust>2 || tmp<thrust ){
        thrust=tmp;
      }
    }
  }
*/
  return  eigenValues(1) ;
}

double
vlq::EventShapeVariables::thrustmajor( unsigned int numberOfSteps ) const
{

	TVectorD eigenValues = compEigenValues(1);

  	return  eigenValues(2) ;
}

