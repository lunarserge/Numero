# Numero

[![GitHub](https://img.shields.io/github/license/lunarserge/Numero)](https://github.com/lunarserge/Numero/blob/master/LICENSE)
[![Build](https://github.com/lunarserge/Numero/actions/workflows/build.yml/badge.svg?branch=master)](https://github.com/lunarserge/Numero/actions/workflows/build.yml)

Connect with the world in a new way.

All of us pass numerous anniversaries in our life. Typically, people count tens of years passed as a significant holiday.
But what if we generalize that towards calculating more anniversaries using other time units? Like celebrating anniversaries in weeks or seconds in addition to years?
For what it worth, one billion seconds anniversary happens approximately when you are about 31 years and 8 months old. Won't it be fun to celebrate such a thing? Numero can do the calculation for you.

And Numero goes one step further. It can use any group of people to calculate joint holidays. Imagine yourself and your significant other and all your kids together to jointly be 100 years old.
That would be a great milestone to celebrate.

Finally, you don't have to be a human being to participate. There is nothing wrong with using anything that has an age.
Like celebrating joint 100 years of a complete family, also including your cars and a house.

Usage (from the command line):

    "Numero.exe" [options] Dates.csv

Options:
* --h:                   produce help message
* --n arg (=100):        limit number of holidays in the output to n lines
* --tz arg:              specify output time zone

Dates.csv: input dates in CSV (Comma Delimited) format.

Numero will output nearest holidays sorted from the nearest towards more distant and specify a group that is having each holiday.

## Usage Details

### Options

**--h**: Produces help message, nothing else to say about it.

**--n**: For a reasonably sized group the output can easily overflow the shell window. Thus, this option limits the number of lines in the output (with 100 closest holidays being the default).

**--tz**: The exact holiday time depends on where you are regarding to time zones. By default, Numero uses the local time zone.
But if you are doing the calculation for somebody else (like intend to give it to your mother living in another time zone) then you may want to use this option.
The target time zone is specified by a value from the ID column of `date_time_zonespec.csv` file that is redistributed with Numero - so look there to pick what you need.
As a little nit-picking Numero works correctly with daylight saving time.

**Dates.csv** is the file with input dates (like birth day and time for human beings). Could be called anyhow, not necessarily Dates, but csv format is expected.
Numero expects 6 columns in order called Name, Month, Day, Year, Hour and Minute in the top line. Following lines represent people or other entities for the computation.
Possible values for these columns are obvious. The input date and time is assumed to be provided in GMT time zone. Thus, you need to take it into account if you want to be precise.
See `TechFriends.csv` for an example of an input file.

### Output

Numero uses the following units of time for the holiday computation:
* second
* minute
* hour
* day
* month (defined as 1/12 of the year, i.e. not exactly normal months)
* year (defined as an average length of the Gregorian year which equals to 365.2425 days)
* week
* quarter (3 months)
* fortnight (2 weeks)
* lustrum (5 years)
* olympiad (4 years)

Only holidays representing whole anniversaries are reported (i.e. starting with '1' and followed by zero or more '0's).

Notice, that your holiday may be off from where you would expect it to be.
E.g., if you celebrate alone you would probably expect things like your 10-year anniversary to happen on the same day and time just 10 years after your birth year.
This is not what Numero will output because of the year definition above. That is the expected behavior and is a right one if you want to measure age in equal units.
Otherwise you'd be in trouble if, e.g., you are born on Feb 29th.

## Implementation Notes

`numero.h` has a few type declarations that may need modification based on the build requirements.
`group_id_t` deserves a special notice as it has a direct effect on the number of entities that could be processed. Basically, each entity needs a bit, so big enough integer type may need to be used.

There are couple of self-explaining inline comments in numero.cpp / main re design choices made that may need to be reconsidered if performance or memory consumption becomes a bottleneck.

Numero depends quite a bit on Boost C++ libraries (http://boost.org). See `NOTICE.txt` for the license terms.

I am using Visual Studio 2019 for the development. Perform these steps for a complete build from source:
1. `git clone --recurse-submodules https://github.com/lunarserge/Numero ` (clone the repository, including the Boost submodule dependency)
2. `cd Numero\boost`
3. `bootstrap` (prepare the Boost.Build system for use, see https://www.boost.org/doc/libs/1_75_0/more/getting_started/windows.html#simplified-build-from-source)
4. `.\b2 --with-program_options --with-date_time` (invoke Boost.Build to build required Boost libraries)
5. Launch Visual Studio and complete the solution build from there

## Release 1.0 Notes

Numero 1.0 is built with Boost version 1.75.0

Input file with up to 16 entities is supported. I am looking for user input to see if this should be increased in the future releases (if any).

The release is built for Windows only. Looking for user input here as well to see if there is enough interest in supporting more targets.

## Finally

I think this is a cool idea to be really used either in a mobile app and/or with a social network. Many of us are accustomed with Facebook reminding us that certain contact person has a birthday.
Won't it be cool to be notified when you have a joint fun date with a subset of your contacts? Basically, command line Numero as it is today is a working application but is a prototype in a sense.

Also, I do have more ideas along the lines of age numbers that I'd implement if I had more time and motivation.
If you want to do something serious with this project and want to know the additional ideas - get in touch with me via email.
That would be my GitHub username at Gmail (sorry, trying a little to prevent email harvesting here).

I don't have enough passion to pursue this idea as a business myself, so don't mind anybody taking it and monetizing the way you like.
Feel free to contact me for those additional ideas or better hire me as your product manager :)
