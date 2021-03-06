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

Description
    Starts timing CPU usage and return elapsed time from start.

\*---------------------------------------------------------------------------*/

#include "cpuTime.H"

#include <unistd.h>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Static Members  * * * * * * * * * * * * * * //

long cpuTime::Hz_(sysconf(_SC_CLK_TCK));


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void cpuTime::getTime(struct tms& t)
{
    times(&t);
}


double cpuTime::timeDifference
(
    const struct tms& start,
    const struct tms& end
)
{
    return
    (
        double
        (
            (end.tms_utime + end.tms_stime)
          - (start.tms_utime + start.tms_stime)
        )/Hz_
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

cpuTime::cpuTime()
{
    getTime(startTime_);
    lastTime_ = startTime_;
    newTime_ = startTime_;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

double cpuTime::elapsedCpuTime() const
{
    getTime(newTime_);
    return timeDifference(startTime_, newTime_);
}


double cpuTime::cpuTimeIncrement() const
{
    lastTime_ = newTime_;
    getTime(newTime_);
    return timeDifference(lastTime_, newTime_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
