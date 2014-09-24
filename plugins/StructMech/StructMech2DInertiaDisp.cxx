#include "StructMech/StructMech.hh"
#include "StructMech2DInertiaDisp.hh"
#include "StructMech2DInertiaVarSet.hh"
#include "Environment/ObjectProvider.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {

    namespace StructMech {

//////////////////////////////////////////////////////////////////////////////

Environment::ObjectProvider<StructMech2DInertiaDisp, InertiaVarSet, StructMechModule, 1>
structMech2DInertiaDispProvider("StructMech2DInertiaDisp");

//////////////////////////////////////////////////////////////////////////////

StructMech2DInertiaDisp::StructMech2DInertiaDisp(const std::string& name) :
  StructMech2DInertiaVarSet(name)
{
  vector<std::string> names(2);
  names[0] = "u";
  names[1] = "v";
  setVarNames(names);
}

//////////////////////////////////////////////////////////////////////////////

StructMech2DInertiaDisp::~StructMech2DInertiaDisp()
{
}

//////////////////////////////////////////////////////////////////////////////

void StructMech2DInertiaDisp::setup()
{
  CFAUTOTRACE;

  StructMech2DInertiaVarSet::setup();

  _rho = getModel()->getDensity();
}

//////////////////////////////////////////////////////////////////////////////

void StructMech2DInertiaDisp::configure ( Config::ConfigArgs& args )
{
  StructMech2DInertiaVarSet::configure(args);
}

//////////////////////////////////////////////////////////////////////////////

    } // namespace StructMech

  } // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////