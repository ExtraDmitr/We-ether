//Exercise 13 (NewContract .sol)

// contracts/Box.sol
// SPDX-License-Identifier: MIT
pragma solidity >=0.5.0 <0.9.0;

// Import Ownable from the OpenZeppelin Contracts library
import "@openzeppelin/contracts/access/Ownable.sol";

// Make Box inherit from the Ownable contract
contract Box is Ownable {
    uint256 private _value;

    event ValueChanged(uint256 value);

    constructor() Ownable(msg.sender) {}

    // The onlyOwner modifier restricts who can call the store function
    function store(uint256 value) public onlyOwner {
        _value = value;
        emit ValueChanged(value);
    }

    function retrieve() public view returns (uint256) {
        return _value;
    }
}
//Exercise 14
contract UserValidation {
    mapping(uint => uint) public age;

    modifier olderThan(uint _age, uint _userId) {
        require(age[_userId] >= _age, "User must be older than the specified age");
        _;
    }

    function validationUsers(uint _userId) public view olderThan(18, _userId) {
            // Function body empty
    }
}
