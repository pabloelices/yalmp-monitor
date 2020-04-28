########################################################################################################################
#                                                                                                                      #
# YALMP Monitor <https://github.com/pabloelices/yalmp-monitor/>                                                        #
# Copyright (C) 2020  Pablo Daniel Gómez Elices                                                                        #
#                                                                                                                      #
# This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public    #
# License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later #
# version.                                                                                                             #
#                                                                                                                      #
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied   #
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more        #
# details.                                                                                                             #
#                                                                                                                      #
# You should have received a copy of the GNU General Public License along with this program.  If not, see              #
# <http://www.gnu.org/licenses/>.                                                                                      #
#                                                                                                                      #
########################################################################################################################

#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: bash generate-appimage.sh <QT_KIT> <APPIMAGE_VERSION>"
    exit 1
fi

# Configuration.

qt_kit_directory=$1
app_image_version=$2

# Directories.

project_root_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

deployment_subdirectory=$project_root_directory/deployment/linux

build_directory=$deployment_subdirectory/build

# Save working directory so it can be restored later.

initial_working_directory=$(pwd)

# Clean deployment_subdirectory.

rm -rf $build_directory
rm -rf $deployment_subdirectory/yalmp-monitor.AppDir
rm -rf $deployment_subdirectory/*.AppImage

# Generate build.

mkdir -p $build_directory

cd $build_directory

$qt_kit_directory/bin/qmake -spec linux-g++ "CONFIG += release" $project_root_directory/yalmp-monitor.pro

make -j$(nproc) qmake_all

pushd yalmp-monitor-core; make -j$(nproc); popd
pushd yalmp-monitor-ui; make -j$(nproc); popd

cd $project_root_directory

# Prepare AppDir.

cp -r $deployment_subdirectory/yalmp-monitor.AppDir.skeleton $deployment_subdirectory/yalmp-monitor.AppDir

cp $build_directory/yalmp-monitor-ui/yalmp-monitor-ui $deployment_subdirectory/yalmp-monitor.AppDir/usr/bin/yalmp-monitor

rm -f $deployment_subdirectory/yalmp-monitor.AppDir/usr/bin/.gitkeep

# Generate AppImage.

export LD_LIBRARY_PATH=$qt_kit_directory/lib:$build_directory/yalmp-monitor-core
export QMAKE=$qt_kit_directory/bin/qmake
export VERSION=$app_image_version

linuxdeploy --appdir $deployment_subdirectory/yalmp-monitor.AppDir --plugin qt --output appimage

mv $project_root_directory/*.AppImage $deployment_subdirectory

# Restore working directory.

cd $initial_working_directory
