// SPDX-License-Identifier: Unlicensed
pragma solidity 0.8.18;

contract DemoContract {
    
    address public owner;
    uint256 public constant TOKEN_PRICE = 2 ether; // Cost of one token in Ether

    struct Receivers {
        string name;
        uint256 tokens;
    }

    mapping(address => Receivers) public users;

    // Modifier to ensure only the owner can execute certain functions
    modifier onlyOwner() {
        require(msg.sender == owner, "Only the owner can perform this action.");
        _;
    }

    constructor() {
        owner = msg.sender;
        users[owner].tokens = 100;
    }

    function double(uint _value) public pure returns (uint) {
        return _value * 2;
    }

    function register(string memory _name) public {
        users[msg.sender].name = _name;
    }
    
    function giveToken(address _receiver, uint256 _amount) public onlyOwner {
        require(users[owner].tokens >= _amount, "Not enough tokens in the owner's balance.");
        users[owner].tokens -= _amount;
        users[_receiver].tokens += _amount;
    }

    // Function to buy tokens
    function buyTokens() public payable {
        uint256 tokensToBuy = msg.value / TOKEN_PRICE;
        require(msg.value >= TOKEN_PRICE, "Minimum purchase is 1 token worth 2 Ether.");
        require(users[owner].tokens >= tokensToBuy, "Owner does not have enough tokens.");

        users[owner].tokens -= tokensToBuy;
        users[msg.sender].tokens += tokensToBuy;
    }

    // Function to display the amount of Ether in the contract
    function getContractBalance() public view returns (uint) {
        return address(this).balance;
    }
}
