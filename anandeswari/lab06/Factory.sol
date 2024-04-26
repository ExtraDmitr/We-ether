//SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.5.0 <0.8.0; 

struct Product /* excercise 4 */
{ 
  uint id;
  string name;
}

contract Factory /* excercise 1 */
{
  uint idDigits = 16;    /* excercise 2 */
  uint idModulus = 10**idDigits; /* excercise 3 */
  Product [] public products; /* exercise 5 */

  function createProduct(string memory _name, uint _id) /* exercise 6 */
    private 
    {
      Product memory newProduct = Product(_id, _name);
      uint ProductId = products.length;
      products.push(newProduct);
      emit NewProduct(ProductId, _name, _id);
    }

  function generateRandomId(string memory _str) /* exercise 7 */
    private view returns (uint)
    {
      uint rand = uint (keccak256(abi.encodePacked("_str")));
      return rand % idModulus;
    }
  function createRandomProduct(string memory _name) /* exercise 8 */
    public 
    {
      uint randId = generateRandomId(_name);
      createProduct(_name, randId);
    }

  event NewProduct (uint indexed ProductId, string _name, uint _id); /* exercise 9 */
  
  mapping (uint => address) public productToOwner; /* exercise 10 */
    mapping (address => uint) public ownerProductCount;
  function Ownership(uint _productId) 
    public                                                             /* Exercise 11 */
    {
        productToOwner[_productId] = msg.sender;
        ownerProductCount[msg.sender]++;
    }

    function getProductsByOwner(address _owner)                        /* Exercise 12 */
    external view returns (uint[] memory) 
    {
    uint[] memory result = new uint[](ownerProductCount[_owner]);      
    uint counter = 0;
    for (uint i = 0; i < products.length; i++) 
    {
    if (productToOwner[products[i].id] == _owner) 
     {
       result[counter] = i;
       counter++;
      }
    }
    return result;

    }

}



