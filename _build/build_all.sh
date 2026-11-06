#!/bin/bash
set -e
SCRIPT_PATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/build.sh"
bash $SCRIPT_PATH psyche
bash $SCRIPT_PATH thyme
bash $SCRIPT_PATH umi
bash $SCRIPT_PATH munch
bash $SCRIPT_PATH lmi
bash $SCRIPT_PATH cmi
bash $SCRIPT_PATH cas
bash $SCRIPT_PATH apollo
bash $SCRIPT_PATH alioth
bash $SCRIPT_PATH elish
bash $SCRIPT_PATH enuma
bash $SCRIPT_PATH dagu
bash $SCRIPT_PATH pipa

bash $SCRIPT_PATH psyche ksu
bash $SCRIPT_PATH thyme ksu
bash $SCRIPT_PATH umi ksu
bash $SCRIPT_PATH munch ksu
bash $SCRIPT_PATH lmi ksu
bash $SCRIPT_PATH cmi ksu
bash $SCRIPT_PATH cas ksu
bash $SCRIPT_PATH apollo ksu
bash $SCRIPT_PATH alioth ksu
bash $SCRIPT_PATH elish ksu
bash $SCRIPT_PATH enuma ksu
bash $SCRIPT_PATH dagu ksu
bash $SCRIPT_PATH pipa ksu
