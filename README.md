This is a template for esp32 projects based on
- esp-idf and
- arduino-esp32 used as a component
- as well as pubsubclient lib for mqtt communication


Getting Started:
- Checkout this repo with "git clone --recursive [THIS_REPO_URL]"
- cd "[THIS_REPO..]"

------------------------
2 Build system options:
------------------------

Build project on Ubuntu:
./installtoolchain.sh
. ./initpath.sh
cd newproject/
make flash monitor


Using a Docker:
- Install docker package (on Ubuntu: apt install docker.io)
- cd dockerbuild
- ./createDocker.sh 
  Note: On Windows or Mac run commands inside this script
- ./startContainerBash.sh
- cd esp32-project/newproject/
- make flash monitor

