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
    Foam::refCount

Description
    Reference counter for tmp\<field\>.

\*---------------------------------------------------------------------------*/

#ifndef refCount_H
#define refCount_H

#include "bool.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                          Class refCount Declaration
\*---------------------------------------------------------------------------*/

class refCount
{
    // Private data

        int count_;

    // Private member functions

        //- Dissallow copy
        refCount(const refCount&);

        //- Dissallow bitwise assignment
        void operator=(const refCount&);


public:

    // Constructors

        //- Construct null with zero count
        refCount()
        :
            count_(0)
        {}


    // Member Functions

        //- Return the reference count
        int count() const
        {
            return count_;
        }


        //- Return true if the reference count is zero
        bool okToDelete() const
        {
            return !count_;
        }


        //- Reset the reference count to zero
        void resetRefCount()
        {
            count_ = 0;
        }


    // Member Operators

        //- Increment the reference count
        void operator++()
        {
            count_++;
        }

        //- Increment the reference count
        void operator++(int)
        {
            count_++;
        }

        //- Decrement the reference count
        void operator--()
        {
            count_--;
        }

        //- Decrement the reference count
        void operator--(int)
        {
            count_--;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
