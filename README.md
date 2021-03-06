# CORE-Dev-Build-1.0
CORE is a 2D Game programming library built using C++. It provides classes and support for dynamic definition and loading of content. Entities can be defined in \*.xml files using a hierarchy of nested xml nodes. CORE also supports animation, sound, responsive GUI's, collision detection, and object prototyping. The next steps in development are to continue defining the central entity class and improving data sharing between components belonging to the same entity.


# Features:

## Entity component system:
CORE is built around its entity-component system. Every object in CORE that can be seen or interacted with is an Entity object. The Entity class has 3 main purposes: to maintain state in a location that provides a common point of access to data members used by multiple child components, to receive and relay events to child components listening for them, and to facilitate communication between sibling components. 

## XML parser:
One of the main features of CORE is the ability to define objects in XML. Entities can be assigned constituent components and variables of a certain name, type, and initial value from xml. CORE also supports XML templating, so users can define shorthand for XML definitions for certain types (see the wiki page for more details - LINK)

## Subsystems:
All top-level functionality and API methods are divided into CORE subsytems. They are listed below roughly in descending order of their importance to the functioning of the engine:

### CORE_Resources:
Provides a common point of access to resources used by various services of the engine. 

### CORE_Factory: 
Used to instantiate and define Entities given a prototype name or XML node. Coupled to constructors for all Entity and Component types in the engine, essentially making it a service locator allowing other engine systems to create specific Component types without necessarily having access to the specific constructor. Can parse XML nodes to read in Entity definitions.

### CORE_TypeTraits:
Provides various functions and structures for determining type information. Mainly used by CORE_Factory and various lower-level engine classes to ensure that type inconsistencies in user defined Entities and Components are detected and properly handled rather than interfering with the kernel directly.

### CORE_Graphics:
Provides an API for managing windows and drawing various things to the screen. 

### CORE_SystemIO
Maintains a set of input and output streams. Currently used to redirect user output 

### CORE_Devices:
Acts as an interface between the various device APIs and the rest of the engine, translating system and input events to engine events. 

### CORE_Audio: 
Interfaces between the audio library of choice and the rest of the engine.

XML parsing for predefined components


In development features:
To do:
The main issue with CORE beyond extensibility and a lack of higher level features is that of cache performance. Currently, CORE preforms an update step by acting an array of pointers to rooms, which contain a vector (another pointer) of pointers to Entities. Each entity stores state data as a map of pointers to Data objects. This level of indirection is torture on the cache, having to follow pointers to pointers to pointers to pointers just to access a single variable for a single component, and then having to follow more pointers to access three next variable in that same component. 


CORE's main design is centered around allowing the user to interact with the engine at as high or low a level as necessary. 

# Design Overview:


# Setup instructions: (move to a seperate file and link from here)
CORE is currently only set up to build in msvc with Visual Studio 2015. It should work with later versions as well, but I haven't tried. If you would like to build instead with an earlier version or cmake or the like, just let me know and I can add build configurations for those. To build, just clone the repository, open the solution in VS 2015, and build. 





Standing Issues:


There is more coupling than I would like between implementation specific functions and classes belonging to third party libraries like SDL and PugiXML. In the future, once the lower level systems of the engine are nailed down more decisively I'd like to make some changes to the easy CORE deals with third party libraries. Rather than directly calling these libraries directly, CORE graphics, sound, etc will provide a common API for the functionality they support. This should allow nearly any third party library to be used as long as the proper wrappers are provided to translate CORE API calls to three specific third party library's calls


Using the Engine: (Move to another file and link from here)


# XML

## Templating
Templates can be defined to allow less verbose instantiations of certain object types

Take for example the following imageElement:
```XML
<ImageElement>
  <xOffset>200</x>
  <yOffset>100</y>
  <image>sprites/foo.png</image>
</ImageElement>
```
If there are many similar instances of ImageElemtent used in a project, adding all of these instances to the XML could become extremely tiresome. Fortunately, a template can be used to simplify this process:
```XML
<templates>
  <ImageElement name="foo">
    <xOffset type="constant">200</xOffset>
    <yOffset type="constant">200</yOffset>
    <image type="main"/>
  </ImageElement>
</templates>
```
Using this template, the XML needed to instantiate the above ImageElement is now simply:
```XML
<foo>sprites/foo.png</foo>
```
### Using XML templating
All XML templates must be enclosed in a set of 
```XML 
<templates>
```
tags. The XML node title is the name of the class that the template will be used to instantiate. The "name" variable in the main header is the template's global name, which will take the place of the class name in any instantiations of this template.

### Template Variables

Templates are used to provide various shorthands for instantiating the variables of a given class. To define a shoirthand for a variable, simply place the variable within the template definition and give it a "type" variable. The use cases for the various type values are enumerated below:

#### Main

The given variable in any instantiation of the template will be gotten from the main value of the node. For example,
```XML
<ImageElement name="bar">
  <image type=main/>
</ImageElement>
```
becomes:
```XML
<bar>sprites/a.png</bar>
```

Since this takes up the entire tag, each template can only have one main value, and any other variables must either be constant, or given their values inside the actual tag, as in:
```XML
<bar x=200, y=200>sprites/a.png</bar>
```

#### Default

The given variable will have a default value that can be overriden:
```XML
<ImageElement name="foo">
  <image type="default">sprites/bar.png</image>
</ImageElement>
```

We can instantiate the above template in one of two ways:
```XML
<foo name="x1"></foo>

<foo name="x2">
  <image type="default">sprites/buzz.png</image>
</foo>
```

For x1, the value of image will default to sprites/bar.png. x2 overrides this value and takes sprites/buzz.png instead.
  

#### Constant

The given variable is constant and cannot be overriden. An error will be thrown if the user attempts to override it in the instantitation

#### Alias

This allows variable names to be renamed or grouped together. For example:
```XML
<ImageElement name="foo">
  <alias name ="xy">
    <x/>
    <y/>
  </alias>
  <alias name="i">
    <image/>
  </alias>
</ImageElement>
```
Becomes:
```XML
<foo>
  <xy>100,200</xy>
  <i>sprites/bar.png</i>
</foo>
```

This new instance will have x=100, y=200, and image=sprites/bar.png

If the title "main" is given to an alias, it will take the place of the main value, assuming there is no main variable already assigned:

```XML
<ImageElement name="foo">
  <alias name="main">
    <x/><y/><image/>
  </alias>
</ImageElement>
```
Can be instantiated with:
```XML
<foo>100,200,sprites/bar.png</foo>
```
