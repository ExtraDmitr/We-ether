// SPDX-License-Identifier: MIT
// Mehmet KOCABIYIK

//Exercise 1
pragma solidity >=0.5.0 <0.8.0;
//Exercise 2-3
contract Factory {
    uint idDigits = 16;
    uint idModulus = 10^(idDigits);
//Exercise 4-5-6 & changed according to 9
struct Product {
    string name;
    uint id;
    }
    Product[] public products;
    event NewProduct(uint indexed productId, string name, uint id);
    function _creatProduct(string memory _name, uint _productId) private { 
        uint arrayProductId = products.length;
        products.push(Product(_name, _productId));
        emit NewProduct(arrayProductId, _name, _productId);
    
    }
//Exercise 7-8    
    function _generateRandomId(string memory _str) private view returns (uint) {
        uint rand = uint(keccak256(abi.encodePacked(_str)));
        return rand % idModulus;

    }
    function creatRandomProduct(string memory _name) public {
        uint randId = _generateRandomId(_name);
        _creatProduct(_name, randId);
    }
// Exercise 10
    mapping (uint => address) public productToOwner;
    mapping (address => uint) ownerProductCount; 
// Exercise 11 
    function Ownership(uint _productId) public {
        productToOwner[_productId] = msg.sender;
        ownerProductCount[msg.sender]++;
    }          
// Exercise 12
   function getProductsByOwner(address _owner) external view returns (uint[] memory)
   {
        uint counter = 0;
        uint[] memory result = new uint[](ownerProductCount[_owner]);

        for (uint i = 0; i < products.length; i++) {
            if (productToOwner[i] == _owner) {
                result[counter] = i;
                counter++;
            }
        }

        return result;
   }
}