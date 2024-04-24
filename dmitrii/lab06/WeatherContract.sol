// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract MarineWeatherStation {

    struct WeatherData {
        uint256 timestamp;
        uint256 temperature;
        uint256 humidity;
        string latitude;
        string longitude;
        address deviceId;
    }

    address public owner;

    // Array to store weather data
    WeatherData[] public weatherData;

    // Mapping from device ID to a boolean indicating whether it's authorized
    mapping(address => bool) public authorizedDevices;

    // Event that is emitted when new weather data is recorded
    event WeatherDataRecorded(uint256 indexed timestamp, address indexed deviceId);

    // Modifier to check if the sender is authorized to submit data
    modifier onlyAuthorizedDevices() {
        require(authorizedDevices[msg.sender], "Device not authorized");
        _;
    }

    constructor() {
        owner = msg.sender;
    }

    // Function to authorize a new device
    function authorizeDevice(address _deviceId) external {
        require(msg.sender == owner, "Only the owner can authorize devices");
        authorizedDevices[_deviceId] = true;
    }

    // Function to submit weather data
    function submitWeatherData(uint256 _temperature, uint256 _humidity, string memory _latitude, string memory _longitude) external onlyAuthorizedDevices {
        weatherData.push(WeatherData(block.timestamp, _temperature, _humidity, _latitude, _longitude, msg.sender));
        emit WeatherDataRecorded(block.timestamp, msg.sender);
    }

    // Function to get weather data by index
    function getWeatherData(uint index) public view returns (WeatherData memory) {
        return weatherData[index];
    }
}
