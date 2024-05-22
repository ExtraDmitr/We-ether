// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract MarineWeatherStation {

    struct WeatherData {
        uint256 timestamp;
        uint256 temperature;
        uint256 humidity;
        string latitude;
        string longitude;
        string deviceId;  // Changed from address to string
    }

    address public owner;

    // Array to store weather data
    WeatherData[] public weatherData;

    // Mapping from device ID key to a boolean indicating whether it's authorized
    mapping(string => bool) public authorizedDevices;

    // Event that is emitted when new weather data is recorded
    event WeatherDataRecorded(uint256 indexed timestamp, string indexed deviceId);  // Changed from address to string

    // Modifier to check if the sender is authorized to submit data
    // This now uses a string key for device ID instead of an Ethereum address
    modifier onlyAuthorizedDevices(string memory deviceId) {
        require(authorizedDevices[deviceId], "Device not authorized");
        _;
    }

    constructor() {
        owner = msg.sender;
    }

    // Function to authorize a new device
    // Now accepts a string key
    function authorizeDevice(string memory deviceId) public {
        // require(msg.sender == owner, "Only the owner can authorize devices");
        authorizedDevices[deviceId] = true;
    }

    // Function to submit weather data
    // This now requires the device ID as a string to check authorization
    function submitWeatherData(uint256 _temperature, uint256 _humidity, string memory _latitude, string memory _longitude, string memory deviceId) external onlyAuthorizedDevices(deviceId) {
        weatherData.push(WeatherData(block.timestamp, _temperature, _humidity, _latitude, _longitude, deviceId));
        emit WeatherDataRecorded(block.timestamp, deviceId);
    }

    // Function to get weather data by index
    function getWeatherData(uint index) public view returns (WeatherData memory) {
        return weatherData[index];
    }
}