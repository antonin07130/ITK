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
#ifndef __itkHistogramToProbabilityImageFilter_h
#define __itkHistogramToProbabilityImageFilter_h

#include "itkHistogramToImageFilter.h"

namespace itk
{
/** \class HistogramToProbabilityImageFilter
 * \brief The class takes a histogram as an input and gives the probability
 * image as the output. A pixel, at position I,  in the output image is given by
 *
 * \f[
 * f(I) = \frac{q_I}{\sum_{i \in I} q_I}
 * \f]
 *  where \f$q_I\f$ is the frequency of measurement vector, I.
 *
 * This is the frequency of a measurement vector by the sum of all frequencies =
 * Probability of the the measurement vector
 *
 * The output image is of type float.
 *
 * This is useful in plotting the joint histograms during registration.
 *
 *  \sa HistogramToImageFilter, HistogramToLogProbabilityImageFilter,
 *  HistogramToIntensityImageFilter, HistogramToEntropyImageFilter
 *
 */

namespace Function
{
template< class TInput, class TOutput = float >
class HistogramProbabilityFunction
{
public:

  //Probability function = Number of occurances in each bin /
  //   Total Number of occurances.
  //
  // Returns pixels of float..
  typedef  TOutput OutputPixelType;

  HistogramProbabilityFunction():
    m_TotalFrequency(1) {}

  ~HistogramProbabilityFunction() {}

  inline OutputPixelType operator()(const TInput & A) const
  {
    return static_cast< OutputPixelType >( static_cast< OutputPixelType >( A )
                                           / static_cast< OutputPixelType >( m_TotalFrequency ) );
  }

  void SetTotalFrequency(SizeValueType n)
  {
    m_TotalFrequency = n;
  }

  SizeValueType GetTotalFrequency() const
  {
    return m_TotalFrequency;
  }

private:
  SizeValueType m_TotalFrequency;
};
}

template< class THistogram, unsigned int NDimensions, class TOutputPixel = float >
class ITK_EXPORT HistogramToProbabilityImageFilter:
  public HistogramToImageFilter< THistogram, NDimensions,
                                 Function::HistogramProbabilityFunction< SizeValueType, TOutputPixel > >
{
public:

  /** Standard class typedefs. */
  typedef HistogramToProbabilityImageFilter Self;

  /** Standard "Superclass" typedef. */
  typedef HistogramToImageFilter< THistogram, NDimensions,
                                  Function::HistogramProbabilityFunction< SizeValueType, TOutputPixel > >
  Superclass;

  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Run-time type information (and related methods).   */
  itkTypeMacro(HistogramToProbabilityImageFilter, HistogramToImageFilter);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);
protected:
  HistogramToProbabilityImageFilter() {}
  virtual ~HistogramToProbabilityImageFilter() {}
private:
  HistogramToProbabilityImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);                    //purposely not implemented
};
} // end namespace itk

#endif
