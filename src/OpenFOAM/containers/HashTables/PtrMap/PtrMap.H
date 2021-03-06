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

Class
    Foam::PtrMap

Description
    A HashTable of pointers to objects of type \<T\> with a label key.

See Also
    Map, HashPtrTable

\*---------------------------------------------------------------------------*/

#ifndef PtrMap_H
#define PtrMap_H

#include "HashPtrTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class PtrMap Declaration
\*---------------------------------------------------------------------------*/

template<class T>
class PtrMap
:
    public HashPtrTable<T, label, Hash<label> >
{

public:

    // Constructors

        //- Construct given initial map size
        PtrMap(const label size = 128)
        :
            HashPtrTable<T, label, Hash<label> >(size)
        {}

        //- Construct from Istream
        PtrMap(Istream& is)
        :
            HashPtrTable<T, label, Hash<label> >(is)
        {}

        //- Construct as copy
        PtrMap(const PtrMap<T>& map)
        :
            HashPtrTable<T, label, Hash<label> >(map)
        {}
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
