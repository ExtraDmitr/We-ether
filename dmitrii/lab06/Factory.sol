// SPDX-License-Identifier: GPL-3.0
// Lab 06 of I4EA of SEAS4.0, 23/23
// Tasks performed by Dmitrii A.
// tasks 9 11 12 and 14 with help of GPT4.

pragma solidity >=0.5.0 <=0.8.0;

contract FactoryContr   {

    uint public idDigits = 16;
    uint public idModulus = 10**idDigits;

    mapping (uint => address) productToOwner;
    mapping ( address => uint) ownerProductCount;
    //task 14
    mapping (uint => uint) public age;


    struct Product  {
        string name;
        uint id;
    }

    Product[] public products;

    event NewProduct (uint ArrayProductId, string name, uint id);

    function _createProduct (string memory _name, uint _id) private {
        uint productId = products.length;
        products.push(Product(_name, _id));
        emit NewProduct (productId, _name, _id);
        // new part: task11
        _assignOwnership(productId, msg.sender);
    }
    
    function _generateRandomId (string memory _str) private view returns (uint) {
        uint rand = uint(keccak256(abi.encodePacked(_str)));
        return rand % idModulus;
    }
    
    //task 11
    function _assignOwnership(uint _productId, address _owner) private {
        productToOwner[_productId] = _owner;
        ownerProductCount[_owner]++;
    }
    
    //task 12
    function getProductsByOwner(address _owner) external view returns (uint[] memory) {
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
    
    //task 14
    modifier olderThan(uint _age, uint _userId) {
        require(age[_userId] >= _age, "User is not old enough.");
        _;
    }

    function validateUser(uint _userId) public view olderThan(18, _userId) {
            // empty body
        }

}
