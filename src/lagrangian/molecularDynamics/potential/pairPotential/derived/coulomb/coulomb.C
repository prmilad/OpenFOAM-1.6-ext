/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

\*---------------------------------------------------------------------------*/

#include "coulomb.H"
#include "mathematicalConstants.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace pairPotentials
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(coulomb, 0);

addToRunTimeSelectionTable
(
    pairPotential,
    coulomb,
    dictionary
);

scalar coulomb::oneOverFourPiEps0 =
    1.0/(4.0 * mathematicalConstant::pi * 8.854187817e-12);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

coulomb::coulomb
(
    const word& name,
    const dictionary& pairPotentialProperties
)
:
    pairPotential(name, pairPotentialProperties)
{
    setLookupTables();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

scalar coulomb::unscaledEnergy(const scalar r) const
{
    return oneOverFourPiEps0/r;
}


bool coulomb::read(const dictionary& pairPotentialProperties)
{
    pairPotential::read(pairPotentialProperties);

    return true;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace pairPotentials
} // End namespace Foam

// ************************************************************************* //
