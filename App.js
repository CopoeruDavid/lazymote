import { StatusBar } from 'expo-status-bar';
import { Button, StyleSheet, Text, View, Alert, Pressable, Image  } from 'react-native';
import axios from 'axios';
import logo from './logo1.png'
import uparrow from './uparr.png'
import downarrow from './downarr.png'

export default function App() {

  const WindowDown = () => {
    axios.get('https://adafruit-window.herokuapp.com/windowdown')
  }

  const WindowUp = () => {
    axios.get('https://adafruit-window.herokuapp.com/windowup');
  }

  return (
    <View style={styles.container}>
      <Image
        style={styles.logo}
        source={logo}
      />
      <Pressable style= {styles.button} onPress={WindowUp} >
        {/* <Text style={styles.text}>  Window Up  </Text> */}
        <Image resizeMode="contain" source={uparrow} style={{ width: 300, height: 300}}/>
      </Pressable>
      <Pressable style= {styles.button} onPress={WindowDown} >
        {/* <Text style={styles.text}>Window Down</Text> */}
        <Image resizeMode="contain" source={downarrow} style={{ width: 300, height: 300}}/>
      </Pressable>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    // flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
  button: {
    alignItems: 'center',
    justifyContent: 'center',
    // paddingVertical: 12,
    // paddingHorizontal: 20,
    // borderRadius: 15,
    // elevation: 1,
    // backgroundColor: 'black',
    marginBottom: -50,
  },
  text: {
    textAlign: 'center',
    fontSize: 20,
    lineHeight: 21,
    fontWeight: 'bold',
    letterSpacing: 0.25,
    color: 'white',
  },
  logo: {
    width: 240,
    height: 170,
    marginBottom: 30,
    marginTop:20,
    marginLeft:-20
  },
});
