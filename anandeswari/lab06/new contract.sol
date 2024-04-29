(new contract .sol file)                    /* Exercise 13 */
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
        function store(uint256 value) public onlyOwner 
        {
            _value = value;
            emit ValueChanged(value);
        }

        function retrieve() public view returns (uint256) 
        {
            return _value;
        }
    }


    contract UserValidation                                 /* Exercise 14 */
    {                            
    mapping(uint => uint) public age;

        modifier olderThan(uint _age, uint _userId) 
    {
            require(age[_userId] >= _age, "User must be older than the specified age");
            _;
    }

        function validationUsers(uint _userId) public view olderThan(18, _userId) 
        {
            // Function body intentionally left blank
        }
    }


// SPDX-License-Identifier: Unlicenced                /* Exercise 15 */
pragma solidity >=0.5.0 <0.9.0;
contract DemoContract 
    {
    address public owner;
    struct Receivers 
        {
        string name;
        uint256 tokens;
        }
    mapping(address => Receivers) public users;
    modifier onlyOwner(){
        require(msg.sender == owner);
        _;
    }
    constructor()
    {
        owner = msg.sender;
        users[owner].tokens = 100;
    }
    function double(uint _value) public pure returns (uint)
    {
        return _value*2;
    }
    function register(string memory _name) public
    {
        users[msg.sender].name = _name;
    }
    function giveToken(address _receiver, uint256 _amount) onlyOwner
    public
    {
        require(users[owner].tokens >= _amount);
        users[owner].tokens -= _amount;
        users[_receiver].tokens += _amount;
    }
 // Function to purchase tokens with Ether
    function buyTokens() public payable {
        // Calculate the number of tokens that can be purchased with the sent Ether
        uint256 tokensToBuy = msg.value / 2; // 1 token = 2 Ether

        // Check if the owner has enough tokens
        require(users[owner].tokens >= tokensToBuy, "Owner does not have enough tokens");

        // Update the balances
        users[owner].tokens -= tokensToBuy;
        users[msg.sender].tokens += tokensToBuy;
    }
}
