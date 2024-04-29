// SPDX-License-Identifier: Unlicensed
pragma solidity >=0.5.0 <0.9.0;

contract DemoContract {
    address public owner;
    uint256 public tokenPrice = 2 ether; // Price of one token
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
        return _value * 2;
    }

    function register(string memory _name) public {
        users[msg.sender].name = _name;
    }

    function buyTokens(uint256 _amount) public payable {
        require(msg.value >= _amount * tokenPrice, "Insufficient Ether sent");
        require(users[owner].tokens >= _amount, "Owner doesn't have enough tokens");

        users[owner].tokens -= _amount;
        users[msg.sender].tokens += _amount;
    }

    function withdraw() public onlyOwner {
        payable(owner).transfer(address(this).balance); // Transfer contract balance to owner
    }
}