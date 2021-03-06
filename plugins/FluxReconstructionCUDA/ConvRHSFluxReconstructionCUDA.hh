#ifndef COOLFluiD_FluxReconstructionCUDA_ConvRHSFluxReconstructionCUDA_hh
#define COOLFluiD_FluxReconstructionCUDA_ConvRHSFluxReconstructionCUDA_hh

//////////////////////////////////////////////////////////////////////////////

#include "FluxReconstructionMethod/ConvRHSFluxReconstruction.hh"
#include "FluxReconstructionMethod/KernelData.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Framework {
    class CellConn;
  }

    namespace FluxReconstructionMethod {
      
//////////////////////////////////////////////////////////////////////////////

/**
 * This class represent a command that computes the convective RHS using
 * FR with CUDA bindings
 *
 * @author Ray Vandenhoeck
 *
 */
template <typename SCHEME, typename PHYSICS, CFuint NB_BLOCK_THREADS>
class ConvRHSFluxReconstructionCUDA : public ConvRHSFluxReconstruction {
public:

  /**
   * Constructor.
   */
  explicit ConvRHSFluxReconstructionCUDA(const std::string& name);
  
  /**
   * Destructor.
   */
  virtual ~ConvRHSFluxReconstructionCUDA();
  
  /**
   * Defines the Config Option's of this class
   * @param options a OptionList where to add the Option's
   */
  static void defineConfigOptions(Config::OptionList& options);

  /**
   * Set up private data and data of the aggregated classes
   * in this command before processing phase
   */
  virtual void setup();
  
  /**
   * Un Setup private data and data of the aggregated classes
   * in this command after processing phase
   */
  virtual void unsetup();
  
  /**
   * Configures the command.
   */
  virtual void configure ( Config::ConfigArgs& args );

  /**
   * Execute Processing actions
   */
  virtual void execute();
      
  /**
   * Returns the DataSocket's that this command needs as sinks
   * @return a vector of SafePtr with the DataSockets
   */
  virtual std::vector<Common::SafePtr<Framework::BaseDataSocketSink> > needsSockets();

protected:
  
  /// Initialize the computation of RHS
  virtual void initializeComputationRHS();
  
  /// Store the stencil data
  virtual void storeStencilData();
  
  /// Copy the local connectivity data to GPU
  void copyLocalCellConnectivity();
  
protected:
  
  /// storage for the stencil via pointers to neighbors
  Framework::DataSocketSink<std::vector<Framework::State*> > socket_stencil;
  
  /// storage for the states
  Framework::DataSocketSink < Framework::State* , Framework::GLOBAL > socket_states;
  
  /// cell-face connectivity
  Common::SafePtr< Common::ConnectivityTable<CFuint> > m_cellFaces;
  
  /// storage of useful cell info: 
  /// in [cellID*5+0] - ptr to corresponding stencil
  /// in [cellID*5+1] - stencil size
  /// in [cellID*5+2] - number of cell faces
  /// in [cellID*5+3] - cell geoshape
  /// in [cellID*5+4] - number of active cell faces (partition faces are excluded)  
  Framework::LocalArray<CFuint>::MALLOC_TYPE m_cellInfo;
  
  /// stencil connectivity for cellID: 
  /// starts at m_cellInfo[cellID*5]
  /// its size is given by m_cellInfo[cellID*5+1]
  /// first m_cellInfo[cellID*5+2] are faces
  Framework::LocalArray<CFuint>::MALLOC_TYPE m_cellStencil;
  
  /// storage of flags for neighbors (1: internal, 0:partition, <0: boundary)
  /// starts at m_cellInfo[cellID*5]
  /// its size is given by m_cellInfo[cellID*5+1]
  /// first m_cellInfo[cellID*5+2] are faces
  Framework::LocalArray<CFint>::MALLOC_TYPE m_neighborTypes;
  
  // cell connectivity
  Framework::LocalArray<Framework::CellConn>::MALLOC_TYPE m_cellConn;
  
  /// number of blocks in x 
  CFuint m_nbBlocksPerGridX;
  
  /// number of blocks in y
  CFuint m_nbBlocksPerGridY;
  
  /// number of cells per block
  CFuint m_nbCellsPerBlock;

  /// number of OpenMP threads
  CFuint m_nbThreadsOMP;
   
  /// flag telling to solve on GPU
  bool m_onGPU;
  
}; // class FVMCC_ComputeRHSCell

//////////////////////////////////////////////////////////////////////////////

    } // namespace FluxReconstructionMethod

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#include "ConvRHSFluxReconstructionCUDA.ci"

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_FluxReconstructionCUDA_ConvRHSFluxReconstructionCUDA_hh
