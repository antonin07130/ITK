/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkQuadEdgeMeshMacro_h
#define __itkQuadEdgeMeshMacro_h

namespace itk
{
//////////////////////////////////////////////////////////////////////////////
/** \def itkQEMeshForAllPointsMacro
 * \brief Iterate on all the itkQE::Points of a given itkQE::Mesh instance.
 *
 * @param MeshType      The type of the itkQE::MeshType
 * @param MeshInstance  The instance of the above MeshType we are considering
 * @param PointVariable The name of the variable the caller wants to use to
 *        designate the MeshType::PointType at current stage of iteration.
 *        The variable PointVariable is of type itkQE::Mesh::PointType.
 * @param PointIndex    The name of the variable the caller wants to use to
 *        designate the index within the MeshType::PointContainer container
 *        and corresponding to PointVariable at current stage of iteration.
 *        The variable PointIndex is of type itkQE::Mesh::PointIdentifier .
 *
 * \author Alexandre Gouaillard, Leonardo Florez-Valencia, Eric Boix
 *
 * This implementation was contributed as a paper to the Insight Journal
 * http://insight-journal.org/midas/handle.php?handle=1926/306
 *
 * \warning Don't forget to close the opened block with the corresponding
 *          itkQE::itkQEMeshForAllPointsMacro macro.
 * \example itkQE::MeshExtractComponentFilter::GetOutput().
 */
#define itkQEMeshForAllPointsMacro(MeshType,                               \
                                   MeshInstance,                           \
                                   PointVariable,                          \
                                   PointIndex)                             \
    {                                                                      \
    typedef typename MeshType::PointType       PointType;                  \
    typedef typename MeshType::PointIdentifier PointIdentifier;            \
    typedef typename MeshType::PointsContainer PointsContainer;            \
    typedef typename MeshType::PointsContainerIterator                     \
    PointsContainerIterator;                                               \
                                                                           \
    PointsContainer *points = ( MeshInstance )->GetPoints();               \
    /* If no points container are present, do nothing */                   \
    if ( !points )                                                         \
      {                                                                    \
      itkWarningMacro("No point container in itkQEMeshForAllPointsMacro"); \
      }                                                                    \
    else                                                                   \
      {                                                                    \
      PointsContainerIterator pointIterator = points->Begin();             \
      while ( pointIterator != points->End() )                             \
        {                                                                  \
        PointType       PointVariable = pointIterator.Value();             \
        PointIdentifier PointIndex = pointIterator.Index();

/** \def itkQEMeshForAllPointsEndMacro
 * \brief Terminates a block of code started with the macro
 *        itkQE::itkQEMeshForAllPointsMacro
 * \warning Should only be used with the corresponding
 *          itkQE::itkQEMeshForAllPointsMacro
 */
#define itkQEMeshForAllPointsEndMacro \
  pointIterator++;                    \
  }    /* while */                    \
  }    /* if */                       \
  }

//////////////////////////////////////////////////////////////////////////////
/** \def itkQEMeshForAllCellsMacro
 * \brief Iterate on all the MeshType::Cells of a given itkQE::Mesh instance.
 *
 * @param MeshType      The type of the itkQE::MeshType
 * @param MeshInstance  The instance of the above MeshType we are considering
 * @param cellIterator  The name of the variable the caller wants to use to
 *        designate the MeshType::CellContainerIterator at current stage of
 *        iteration.
 *
 * \author Alexandre Gouaillard, Leonardo Florez-Valencia, Eric Boix
 *
 * This implementation was contributed as a paper to the Insight Journal
 * http://insight-journal.org/midas/handle.php?handle=1926/306
 *

 * \warning Don't forget to close the opened block with the corresponding
 *          itkQE::itkQEMeshForAllCellsEndMacro macro.
 * \example itkQE::itkQEMeshForAllPrimalEdgesMacro
 */
#define itkQEMeshForAllCellsMacro(MeshType,                                    \
                                  MeshInstance,                                \
                                  cellIterator)                                \
    {                                                                          \
    typedef typename MeshType::CellsContainer CellsContainer;                  \
    typedef typename MeshType::CellsContainerIterator                          \
    CellsContainerIterator;                                                    \
    /* If no cells are present, do nothing */                                  \
    if ( !MeshInstance->GetCells() )                                           \
      {                                                                        \
      itkWarningMacro("No Cells container in itkQEMeshForAllCellsMacro");      \
      }                                                                        \
    else                                                                       \
      {                                                                        \
      CellsContainerIterator cellIterator = MeshInstance->GetCells()->Begin(); \
      while ( cellIterator != MeshInstance->GetCells()->End() )                \
        {                                                                      \
        /* Users code comes here: */

/** \def itkQEMeshForAllCellsEndMacro
 * \brief Terminates a block of code started with the macro
 *        itkQE::itkQEMeshForAllCellsMacro
 * \warning Should only be used with the corresponding
 *          itkQE::itkQEMeshForAllCellsMacro
 */
#define itkQEMeshForAllCellsEndMacro(cellIterator) \
  cellIterator++;                                  \
  }    /* while */                                 \
  }    /* if */                                    \
  }

//////////////////////////////////////////////////////////////////////////////
/** \def itkQEMeshForAllPrimalEdgesMacro
 * \brief Iterate on all the MeshType::QEPrimal* of a given itkQE::Mesh instance
 *
 * @param MeshType      The type of the itkQE::MeshType
 * @param MeshInstance  The instance of the above MeshType we are considering
 * @param EdgeVariable  The name of the variable the caller wants to use to
 *        designate the MeshType::QEPrimal* at current stage of iteration.
 *
 * \author Alexandre Gouaillard, Leonardo Florez-Valencia, Eric Boix
 *
 * This implementation was contributed as a paper to the Insight Journal
 * http://insight-journal.org/midas/handle.php?handle=1926/306
 *
 * \warning Don't forget to close the opened block with the corresponding
 *          itkQE::itkQEMeshForAllPrimalEdgesMacro macro.
 */
#define itkQEMeshForAllPrimalEdgesMacro(MeshType,                   \
                                        MeshInstance,               \
                                        EdgeVariable)               \
    {                                                               \
    typedef typename MeshType::QEPrimal QEPrimal;                   \
                                                                    \
    itkQEMeshForAllCellsMacro(MeshType, MeshInstance, cellIterator) \
      {                                                             \
      if ( QEPrimal * EdgeVariable =                                \
             dynamic_cast< QEPrimal * >( cellIterator.Value() ) )   \
        {                                                           \
        /* Users code comes here: */

/** \def itkQEMeshForAllPrimalEdgesEndMacro
 * \brief Terminates a block of code started with the macro
 *        itkQE::itkQEMeshForAllPrimalEdgesMacro
 * \warning Should only be used with the corresponding
 *          itkQE::itkQEMeshForAllPrimalEdgesMacro
 */
#define itkQEMeshForAllPrimalEdgesEndMacro \
  }     /* fi */                           \
  }                                        \
  itkQEMeshForAllCellsEndMacro             \
  }
} // end namespace

#endif
