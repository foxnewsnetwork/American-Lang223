== Note to the reader

If you're reading this but you're not Henry or Trevor or me, please
stop reading this. Seriously, no seriously, stop. I mean, it would
be great if I had a private repo which I can use to keep out prying
eyes but I can't afford one so I'm using obfuscating names to try
to keep some of the people out. 

One day, when our startup can depart the bootstrapping phase and
enter the have-funding scaling-up phase, we'll get a private repo
on github or gitorious but, in the meantime, here's to hoping the
subject of American Language at a graduate level is deathly dull to
anyone reading.

== Indigio / Ingidio Desktop Application

Contained in the IndigioApp is the C# code for the first incarnation
of the Indigio appplication for the Windows 7 desktop game recorder.

Like a ruby-rails application, this one is done in the traditional
MVC style. Because of the desktop nature of this system, a good
windows machine with .NET and traditional WINAPIs are required to
actually run this. 

== Layout

The IndigioApp folder is the only one that contains executeable 
content. All the other folders are projects to DLLs and assemblies
that are called from within IndigioApp. 

== Things to note

In starcraft 2, supply counts are kept at 4096 * N where N is the
value you see on your screen when playing.

The same is true for unit health; divide out by 4096 first to get
the on-screen health difference.

Army_size is the total number of harvesters + units + buildings
you have on the map

The units structure is sized by the sizeof operator to be 468 bytes
however, only the first 448 bytes are actually what we're looking
for. Going the extra 20 bytes will break everything.