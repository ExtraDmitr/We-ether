//Exercise 15 (NewContract .sol)

// SPDX-License-Identifier: Unlicenced

pragma solidity >=0.5.0 <0.9.0;
contract DemoContract {
    address public owner;
    struct Receivers {
        string name;
        uint256 tokens;
    }
    mapping(address => Receivers) public users;
    modifier onlyOwner(){
        require(msg.sender == owner);
        _;
    }
    constructor(){
        owner = msg.sender;
        users[owner].tokens = 100;
    }
    function double(uint _value) public pure returns (uint){
        return _value*2;
    }
    function register(string memory _name) public{
        users[msg.sender].name = _name;
    }
    function giveToken(address _receiver, uint256 _amount) onlyOwner
    public{
        require(users[owner].tokens >= _amount);
        users[owner].tokens -= _amount;
        users[_receiver].tokens += _amount;
    }
}