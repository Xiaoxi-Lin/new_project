/*

Copyright (c) 2005-2020, University of Oxford.
All rights reserved.

University of Oxford means the Chancellor, Masters and Scholars of the
University of Oxford, having an administrative office at Wellington
Square, Oxford OX1 2JD, UK.

This file is part of Chaste.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
 * Neither the name of the University of Oxford nor the names of its
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef CHEMOTACTICFORCE_PHENOTYPEDEPENDENT_SPECIFYNUTRIENTANDCELLTYPE_HPP_
#define CHEMOTACTICFORCE_PHENOTYPEDEPENDENT_SPECIFYNUTRIENTANDCELLTYPE_HPP_

#include "ChasteSerialization.hpp"
#include <boost/serialization/base_object.hpp>

#include "AbstractForce.hpp"

/**
 * A chemotactic force class.
 */
template<unsigned DIM>
class ChemotacticForce_PhenotypeDependent_SpecifyNutrientAndCellType: public AbstractForce<DIM>
{
friend class TestForces;

private:

    /**
     * @return the magnitude of the chemotactic force.
     *
     * @param concentration the local nutrient concentration
     * @param concentrationGradientMagnitude the magnitude of the local nutrient concentration gradient
     */
    double GetChemotacticForceMagnitude(const double concentration, const double concentrationGradientMagnitude);

    friend class boost::serialization::access;
    /**
     * Boost Serialization method for archiving/checkpointing.
     * Archives the object and its member variables.
     *
     * @param archive  The boost archive.
     * @param version  The current version of this class.
     */
    template<class Archive>
    void serialize(Archive & archive, const unsigned int version)
    {
        archive & boost::serialization::base_object<AbstractForce<DIM> >(*this);
    }
    
    std::string mNutrient;

    std::vector<unsigned> mCellTypesForChemotaxis;

    double mSensitivity;

public:

    /**
     * Constructor.
     */
    ChemotacticForce_PhenotypeDependent_SpecifyNutrientAndCellType();

    /**
     * Destructor.
     */
    ~ChemotacticForce_PhenotypeDependent_SpecifyNutrientAndCellType();

    /**
     * Overridden AddForceContribution() method.
     *
     * @param rCellPopulation reference to the cell population
     *
     * Fc = chi(C,|gradC|) gradC/|gradC|  (if |gradC|>0, else Fc = 0)
     *
     */
    void AddForceContribution(AbstractCellPopulation<DIM>& rCellPopulation);

    /**
     * Overridden OutputForceParameters() method.
     *
     * @param rParamsFile the file stream to which the parameters are output
     */
    void OutputForceParameters(out_stream& rParamsFile);

    void SetNutrient(std::string nutrient);

    std::string GetNutrient();

    std::vector<unsigned> GetCellTypesForChemotaxis();

    void SetCellTypesForChemotaxis(std::vector<unsigned> newCellTypesForChemotaxis);

    double GetSensitivity();

    void SetSensitivity(double newSensitivity);
};

#include "SerializationExportWrapper.hpp"
EXPORT_TEMPLATE_CLASS_SAME_DIMS(ChemotacticForce_PhenotypeDependent_SpecifyNutrientAndCellType)

#endif /*CHEMOTACTICFORCE_PHENOTYPEDEPENDENT_SPECIFYNUTRIENTANDCELLTYPE_HPP_*/
