# design stuff

right so here's the thought for an videojuego

there might be other stuff (tests, tooling?) that might not fit naturally in so there's gonna be the whole library/binary distinction but it'll be like

_most_ code lives in `src/` but the entry points and some specific stuff are in `app/whatever/` maybe that's terribad?

anyway so file directory layout is like (* is untracked/ephemeral folders)

```txt
project/
    CMakeLists.txt
    README.md
    other_top_level_stuff
    cmake/                  cmake specific
    src/                    source of most stuff (libirary ish code)
    lib/*                   output dir for libs (but not for project)
    app/                    source for binary specific stuff (a bit artbitrary tbh)
    bin/*                   output dir for binaries
    build/*                 output for object files
    script/                 developer and building utility
    external/               third party code we pull in but _do not_ vendor via git submodules
    vendor/                 third party code we do vendor, either by forks or tracking changes (mostly lua tbh)
    data/                   location of data assets for game
    doc/                    sourc for docs
    docout/*                 location of doc output 
```

lua has to be pulled in and strategically vendored to be built in to handle our builtins, most others can be statically linked in. external directories should be handled by git subrepos and if necessary a CMakeLists.txt that does glue code for them. 



the high level architecture is assetpools (either fixed one's or `std::vector` probably the former) that you can construct and get stuff from and presumambly you can access with either pointers or handles (tbh handles might be more stable overall??). Entities are things in the world with transforms, actors are more complicated, individual can also react to events (with sublevel event components), for graphics and resource the system is similar and might be implcitily global so you don't have individual AssetManager classes instead that use phantom type varaibles.

```c++
template<typename T>
struct Handle 
{
    template<typename U>
    Handle(Handle<U>) {
        static_assert(! std::is_same_type<U,T>, "invalid handle type passed.");
    }
    int32_t value
};
```

the main class can be a `Game` class which is a variant over `Scene` (or just a ScneeMachine) which has virtual functions which handle inputs, update game state, render, and maybe save

lua integration happens by a bunch of libraries and userdata thats just pointer into the c++ space that expose glue code, very async-style event orriented. there's an abstract callback type that can hold _either_ luabytecode dumped earlier or a native function or _maybe_ a lua registry key, whichever one might be easier to handlde; these would be invoked with `VM::run_script()`.

Entites are an abstract virtual base class that several general types implement (Actors, geometry objects, triggers, so on). Actors have pointers to ActorKinds that hold "methods" and "static variables" where Actors hold some fixed instance variables and a set of variable instance-type variables or a pointer into a `Dict` of values. ActorKinds are also meant to be loaded from a config file (but don't need to be).

configuration can be done via json (jsonc? json++) that can also be used for saving.

For data layout i contemplated a "Campaign" orriented one but that fits in weird with the procgen stuff if this is a roguelike but it would look someting like

```txt
data/
    campaign-foo/       Campaign assets
        manifest.json
        monster/
        model/
        texture/
    general/            General assets     
```

but maybe it makes more sense for it to be the other way around (but thats not as good if there are shared textures??)

there are bump allocators usable for short term things (rednering stuff mainly)

