# Add only the display srcs you are going to use if you want to keep compiled srcs to a minimum:
set(srcs 
    "models/gdew042t2.cpp"
    "models/gdew042t2Grays.cpp"
    "models/color/gdeh042Z21.cpp"
    # Common base classes
    "epd.cpp"
    "epd7color.cpp"
    "epdspi.cpp"
    "epd4spi.cpp"
    )

# If the project does not use a touch display component FT6X36-IDF can be removed or #commented
idf_component_register(SRCS ${srcs}      
                    REQUIRES "Adafruit-GFX"
                    INCLUDE_DIRS "include"
)
# Note about epdiy component: Even if it's not REQUIRED sometimes CMake includes it
#      giving errors. If that happens, just open the component CMakeLists and add:
#      return()
#      As the first line. This will tell CMake to not compile it.
