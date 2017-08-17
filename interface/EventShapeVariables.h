#ifndef ANALYSIS_VLQANA_EventShapeVariables_h
#define ANALYSIS_VLQANA_EventShapeVariables_h

//// Adapted from PhysicsTools/CandUtils/interface/EventShapeVariables.h

#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"

#include "TMatrixDSym.h"
#include "TVectorD.h"

#include <vector>

namespace vlq{
  class EventShapeVariables {

    public:
      /// constructor from XYZ coordinates
      explicit EventShapeVariables(const std::vector<math::XYZVector>& inputVectors);  
      /// constructor from rho eta phi coordinates
      explicit EventShapeVariables(const std::vector<math::RhoEtaPhiVector>& inputVectors);  
      /// constructor from r theta phi coordinates
      explicit EventShapeVariables(const std::vector<math::RThetaPhiVector>& inputVectors);  
      /// default destructor
      ~EventShapeVariables(){};

      /// the return value is 1 for spherical events and 0 for events linear in r-phi. This function 
      /// needs the number of steps to determine how fine the granularity of the algorithm in phi 
      /// should be
      double isotropy(unsigned int numberOfSteps = 1000 ) const;

      /// the return value is 1 for spherical and 0 linear events in r-phi. This function needs the 
      /// number of steps to determine how fine the granularity of the algorithm in phi should be
      double circularity(unsigned int numberOfSteps = 1000 ) const;

      /// 1.5*(q1+q2) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
      /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return values are 1 for spherical, 3/4 for 
      /// plane and 0 for linear events
      double sphericity(double r = 2.) const;
      /// 1.5*q1 where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
      /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return values are 0.5 for spherical and 0 
      /// for plane and linear events
      double aplanarity(double r = 2.) const;
      /// 3.*(q1*q2+q1*q3+q2*q3) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
      /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return value is between 0 and 1 
      /// and measures the 3-jet structure of the event (C vanishes for a "perfect" 2-jet event)
      double C(double r = 2.) const;
      /// 27.*(q1*q2*q3) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
      /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return value is between 0 and 1 
      /// and measures the 4-jet structure of the event (D vanishes for a planar event)
      double D(double r = 2.) const;
      ///
      ///
      ///
      double thrust( unsigned int numberOfSteps = 100 ) const;
      ///
      ///
      ///
      double thrustminor( unsigned int numberOfSteps  = 100 ) const;




    private:
      /// helper function to fill the 3 dimensional momentum tensor from the inputVectors where 
      /// needed
      TMatrixDSym compMomentumTensor(double r = 2.) const;
      TVectorD compEigenValues(double r = 2.) const;

      /// cashing of input vectors
      std::vector<math::XYZVector> inputVectors_;
  };
}
#endif
