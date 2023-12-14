add_requires("libsdl","libsdl_image")
set_languages("cxx17")
set_targetdir("./")
set_objectdir("./objs/$(os)_$(arch)")

rule("fclean")
	 on_clean(function (target)
        -- remove sourcefile.html
    end)

target("Slow")
	add_files("srcs/**.cpp")
	add_includedirs("includes")
	add_packages("libsdl","libsdl_image")
	set_kind("binary")


