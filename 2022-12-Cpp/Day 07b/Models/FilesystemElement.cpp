//
// Created by David on 12/25/2022.
//

#include "FilesystemElement.h"

#include <utility>

FilesystemElement::FilesystemElement(string name, FilesystemElement* pParentAddress, ElementTypes elementType, int size) : pParentAddress(pParentAddress)
{
    Name = std::move(name);
    Type = elementType;
    Size = size;
}
