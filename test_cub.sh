#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

if [ ! -f "./cub3D" ]; then
    echo -e "${RED}Error: ./cub3D does not exist${NC}"
    echo "Please use 'make' first to generate the binary"
    exit 1
fi

test_map() {
    local map=$1
    local expected_result=$2

    echo -e "\n${YELLOW}Testing: ${map}${NC}"
    ./cub3D "$map"
    result=$?

    if [ $expected_result -eq 0 ]; then
        if [ $result -eq 0 ]; then
            echo -e "${GREEN}✓ OK${NC}"
        else
            echo -e "${RED}✗ ERROR: Valid map failed to load${NC}"
        fi
    else
        if [ $result -ne 0 ]; then
            echo -e "${GREEN}✓ OK (Expected error)${NC}"
        else
            echo -e "${RED}✗ ERROR: Invalid map accepted${NC}"
        fi
    fi
}

# Test des bonnes maps
echo -e "\n${YELLOW}=== VALID MAPS ===${NC}"
if [ -d "maps/valid" ]; then
    for map in maps/valid/*; do
        if [ -f "$map" ]; then
            test_map "$map" 0
        fi
    done
else
    echo -e "${RED}ERROR: maps/valid/ directory does not exist${NC}"
fi

# Test des mauvaises maps
echo -e "\n${YELLOW}=== INVALID MAPS ===${NC}"
if [ -d "maps/invalid" ]; then
    for map in maps/invalid/*; do
        if [ -f "$map" ]; then
            test_map "$map" 1
        fi
    done
else
    echo -e "${RED}ERROR: maps/invalid/ directory does not exist${NC}"
fi
