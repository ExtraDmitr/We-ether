// SPDX-License-Identifier: GPL-3.0
// Lab 06 of I4EA of SEAS4.0, 23/24
// Tasks performed by Dmitrii A.
// tasks 9 11 12 and 14 with help of GPT4.

pragma solidity >=0.5.0 <=0.8.0;

contract FactoryContr {
    // Constant variables for ID generation
    uint public idDigits = 16;
    uint public idModulus = 10**idDigits;

    // Mappings to track product ownership and count of products per owner
    mapping (uint => address) productToOwner;
    mapping (address => uint) ownerProductCount;
    // Mapping to store user ages (task 14)
    mapping (uint => uint) public age;

    // Product struct with name and ID
    struct Product {
        string name;
        uint id;
    }

    // Array to store all products
    Product[] public products;

    // Event to be emitted when a new product is created
    event NewProduct (uint ArrayProductId, string name, uint id);

    // Private function to create a product and assign ownership
    function _createProduct (string memory _name, uint _id) private {
        // Calculate the index for the new product
        uint productId = products.length;
        // Add the new product to the array and emit the corresponding event
        products.push(Product(_name, _id));
        emit NewProduct(productId, _name, _id);
        // Assign ownership of the new product to the caller (task 11)
        _assignOwnership(productId, msg.sender);
    }
    
    // Private view function to generate a pseudo-random ID based on input string
    function _generateRandomId (string memory _str) private view returns (uint) {
        uint rand = uint(keccak256(abi.encodePacked(_str)));
        return rand % idModulus;  // Ensure the ID is within the specified range
    }
    
    // Private function to assign ownership of a product
    function _assignOwnership(uint _productId, address _owner) private {
        productToOwner[_productId] = _owner;  // Map product to owner
        ownerProductCount[_owner]++;  // Increment the count of products owned by this owner
    }
    
    // External view function to get products owned by a specific address
    function getProductsByOwner(address _owner) external view returns (uint[] memory) {
        uint counter = 0;
        uint[] memory result = new uint[](ownerProductCount[_owner]);  // Initialize result array with size based on owner product count
        for (uint i = 0; i < products.length; i++) {
            if (productToOwner[i] == _owner) {  // Check if the current product is owned by the specified owner
                result[counter] = i;  // Store the product index
                counter++;  // Increment the counter
            }
        }
        return result;  // Return the array of product indices
    }
    
    // Modifier to check if a user's age meets a specified threshold
    modifier olderThan(uint _age, uint _userId) {
        require(age[_userId] >= _age, "User is not old enough.");  // Enforce age requirement
        _;
    }

    // Public view function to validate a user's age using the olderThan modifier
    function validateUser(uint _userId) public view olderThan(18, _userId) {
            // Function body is intentionally left empty
        }

}
