cmake_minimum_required(VERSION 3.16)

project(MobileRogue C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ----------------------
# Arquivos do projeto
# ----------------------
set(SOURCES
    main.c
    Game.c
    world.c
    input.c
    ui.c
    cards.c
    entities/entities.c
    entities/tower/tower.c
    entities/enemies/enemies.c
    entities/projectiles/projectiles.c
    entities/effects/effects.c
)

add_executable(MobileRogue ${SOURCES})

# ----------------------
# cJSON
# ----------------------
target_link_libraries(MobileRogue PRIVATE cjson)
target_include_directories(MobileRogue PRIVATE /usr/include/cjson)

# ----------------------
# raylib
# ----------------------
add_subdirectory(raylib)
target_link_libraries(MobileRogue PRIVATE raylib)

# ----------------------
# Includes
# ----------------------
target_include_directories(MobileRogue PRIVATE
    .
    Mobile-Rogue/raylib/src
)

# ----------------------
# Linux libs necessárias
# ----------------------
if(UNIX AND NOT APPLE)
    target_link_libraries(MobileRogue PRIVATE
        m pthread dl rt X11
    )
endif()
